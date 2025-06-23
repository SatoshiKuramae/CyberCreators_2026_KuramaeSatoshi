//==============================================================
//
//input.cpp
//
// Author:Satoshi Kuramae
//==============================================================
#include "input.h"

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//コンストラクタ(CInput)
CInput::CInput()
{

}

//デストラクタ(CInput)
CInput::~CInput()
{

}

//初期化
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

//破棄
void CInput::Uninit()
{
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();		//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//CInoutKeyboard実装

//コンストラクタ(CInputKeyboard)
CInputKeyboard::CInputKeyboard()
{

}

//デストラクタ(CInputKeyboard)
CInputKeyboard::~CInputKeyboard()
{

}

//初期化
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED((m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	m_pDevice->Unacquire();
	return S_OK;

}

//破棄
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//更新処理
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();	//キーボードへのアクセス権を獲得
	}
}

//各種入力状態の関数
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//キーボードのリリース情報を更新
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}
//================================================================================================================================
//パッド入力処理
//================================================================================================================================

HRESULT CInputGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//メモリのクリア
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&m_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//終了処理
void CInputGamepad::Uninit()
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);
}

// スティックの入力を方向パッドフラグに変換
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

//ジョイパッドの更新処理
void CInputGamepad::Update()
{
	XINPUT_STATE joykeyState; //ジョイパッドの入力情報

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		CInputGamepad::UpdateStick(&joykeyState);
		joykeyState.Gamepad.wButtons |= GetJoypadStick(joykeyState.Gamepad.sThumbLX, joykeyState.Gamepad.sThumbLY, 8000);
		m_XInput = joykeyState;

		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joyKeyState;
		m_joyKeyStateTrigger = Button & ~OldButton;    // トリガー処理
		m_ajoyKeyStateRelease = ~Button & OldButton;    // リリース処理


		// 現在の時間を取得する
		m_aJoypadCurrentTime = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime - m_aJoypadExecLastTime) > SPEED_KEY))
		{
			// 最後に真を返した時間を保存
			m_aJoypadExecLastTime = m_aJoypadCurrentTime;

			// キーボードのリピート情報を保存
			/*m_joyKeyStateRepeat = joykeyState;*/
		}
		else
		{
			// キーボードのリピート情報を保存
		/*	m_joyKeyStateRepeat.Gamepad.wButtons = 0;*/
		}

		//デッドゾーンの設定
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

		m_joyKeyState = joykeyState.Gamepad.wButtons;                // プレス処理
	}
}

//ジョイパッドのプレス情報を取得
bool CInputGamepad::GetJoypadPress(JOYKEY key)
{
	return (m_joyKeyState & (0x01 << key)) ? true : false;
}

//ジョイパッドのトリガー情報を取得
bool CInputGamepad::GetJoypadTrigger(JOYKEY key)
{
	return (m_joyKeyStateTrigger & (0x01 << key)) ? true : false;
}

bool CInputGamepad::GetJoypadRepeat(JOYKEY key)
{
	return true;
}

//スティックの更新処理
void CInputGamepad::UpdateStick(XINPUT_STATE* stickstate)
{
	m_R_Trigger.y = (stickstate->Gamepad.bRightTrigger / 255.0f);
	m_L_Trigger.y = (stickstate->Gamepad.bLeftTrigger / 255.0f);


}

//2点の角度を求める
float CInputGamepad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //角度

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

// コントローラーの入力情報の取得
XINPUT_STATE* CInputGamepad::GetXInputState(void)
{
	return &m_XInput;
}

// スティックの入力情報を取得
CInputGamepad::STICKINPUT CInputGamepad::GetStick(void)
{
	return m_stick;
}

//パッドの入力情報取得
//float CInputGamepad::GetPadthumb(float padLX, float padLY, float padRX, float padRY)
//{
//	XINPUT_STATE joykeyState; //ジョイパッドの入力情報
//
//	joykeyState.Gamepad.sThumbLX = padLX;
//	joykeyState.Gamepad.sThumbLY = padLY;
//	joykeyState.Gamepad.sThumbRX = padRX;
//	joykeyState.Gamepad.sThumbRY = padRY;
//}
//コンストラクタ
CInputGamepad::CInputGamepad() : m_stick()
{

}
//デストラクタ
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

