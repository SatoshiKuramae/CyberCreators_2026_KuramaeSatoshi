//==============================================================
//
//input.cpp
//
// Author:Satoshi Kuramae
//==============================================================
#include "input.h"

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//�R���X�g���N�^(CInput)
CInput::CInput()
{

}

//�f�X�g���N�^(CInput)
CInput::~CInput()
{

}

//������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION, IID_IDirectInput8,
			(void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//�j��
void CInput::Uninit()
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//CInoutKeyboard����

//�R���X�g���N�^(CInputKeyboard)
CInputKeyboard::CInputKeyboard()
{

}

//�f�X�g���N�^(CInputKeyboard)
CInputKeyboard::~CInputKeyboard()
{

}

//������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED((m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Unacquire();
	return S_OK;

}

//�j��
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//�X�V����
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//�e����͏�Ԃ̊֐�
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//�L�[�{�[�h�̃����[�X�����X�V
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}
//================================================================================================================================
//�p�b�h���͏���
//================================================================================================================================

HRESULT CInputGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&m_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//�I������
void CInputGamepad::Uninit()
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
WORD CInputGamepad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//�W���C�p�b�h�̍X�V����
void CInputGamepad::Update()
{
	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		CInputGamepad::UpdateStick(&joykeyState);
		joykeyState.Gamepad.wButtons |= GetJoypadStick(joykeyState.Gamepad.sThumbLX, joykeyState.Gamepad.sThumbLY, 8000);
		m_XInput = joykeyState;

		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joyKeyState;
		m_joyKeyStateTrigger = Button & ~OldButton;    // �g���K�[����
		m_ajoyKeyStateRelease = ~Button & OldButton;    // �����[�X����


		// ���݂̎��Ԃ��擾����
		m_aJoypadCurrentTime = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime - m_aJoypadExecLastTime) > SPEED_KEY))
		{
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			m_aJoypadExecLastTime = m_aJoypadCurrentTime;

			// �L�[�{�[�h�̃��s�[�g����ۑ�
			/*m_joyKeyStateRepeat = joykeyState;*/
		}
		else
		{
			// �L�[�{�[�h�̃��s�[�g����ۑ�
		/*	m_joyKeyStateRepeat.Gamepad.wButtons = 0;*/
		}

		//�f�b�h�]�[���̐ݒ�
		if (joykeyState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			joykeyState.Gamepad.sThumbLX = 0;
			joykeyState.Gamepad.sThumbLY = 0;
		}
		if (joykeyState.Gamepad.sThumbRX <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbRX >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbRY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			joykeyState.Gamepad.sThumbRY >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			joykeyState.Gamepad.sThumbRX = 0;
			joykeyState.Gamepad.sThumbRY = 0;
		}

		m_joyKeyState = joykeyState.Gamepad.wButtons;                // �v���X����
	}
}

//�W���C�p�b�h�̃v���X�����擾
bool CInputGamepad::GetJoypadPress(JOYKEY key)
{
	return (m_joyKeyState & (0x01 << key)) ? true : false;
}

//�W���C�p�b�h�̃g���K�[�����擾
bool CInputGamepad::GetJoypadTrigger(JOYKEY key)
{
	return (m_joyKeyStateTrigger & (0x01 << key)) ? true : false;
}

bool CInputGamepad::GetJoypadRepeat(JOYKEY key)
{
	return true;
}

//�X�e�B�b�N�̍X�V����
void CInputGamepad::UpdateStick(XINPUT_STATE* stickstate)
{
	m_R_Trigger.y = (stickstate->Gamepad.bRightTrigger / 255.0f);
	m_L_Trigger.y = (stickstate->Gamepad.bLeftTrigger / 255.0f);


}

//2�_�̊p�x�����߂�
float CInputGamepad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //�p�x

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

// �R���g���[���[�̓��͏��̎擾
XINPUT_STATE* CInputGamepad::GetXInputState(void)
{
	return &m_XInput;
}

// �X�e�B�b�N�̓��͏����擾
CInputGamepad::STICKINPUT CInputGamepad::GetStick(void)
{
	return m_stick;
}

//�p�b�h�̓��͏��擾
//float CInputGamepad::GetPadthumb(float padLX, float padLY, float padRX, float padRY)
//{
//	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��
//
//	joykeyState.Gamepad.sThumbLX = padLX;
//	joykeyState.Gamepad.sThumbLY = padLY;
//	joykeyState.Gamepad.sThumbRX = padRX;
//	joykeyState.Gamepad.sThumbRY = padRY;
//}
//�R���X�g���N�^
CInputGamepad::CInputGamepad() : m_stick()
{

}
//�f�X�g���N�^
CInputGamepad::~CInputGamepad()
{

}

float CInputGamepad::GetJoyLX()
{
	if (XInputGetState(0, &m_XInput) == ERROR_SUCCESS)
	{
		return (float)(m_XInput.Gamepad.sThumbLX);
	}
	return 0.0f;
}

float CInputGamepad::GetJoyLY()
{
	if (XInputGetState(0, &m_XInput) == ERROR_SUCCESS)
	{
		return (float)(m_XInput.Gamepad.sThumbLY);
	}
	return 0.0f;
}

