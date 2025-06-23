//============================================================
//
//input.h
//Author Kuramaesatoshi
//============================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"
#include "dinput.h"
#include "d3dx9.h" //�`�揈���ɕK�v"
#include "Xinput.h"//�W���C�p�b�h
#include "xaudio2.h"
constexpr int MAX_KEY(256);
constexpr int JOYPAD_DEADZONE(1);
constexpr int SPEED_KEY(1);
//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")		//�`�揈���ɕK�v
#pragma	comment(lib, "d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")	//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib, "winmm.lib")	//�V�X�e�������擾���ɕK�v
#pragma comment(lib, "dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib") //�W���C�p�b�h

//���͊��N���X
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;

protected:
	//�S���͏����ŋ��L
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h����
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRelease(int nKey);
protected:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];

};

//�p�b�h����
class CInputGamepad :public CInput
{
public:
	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	//�X�e�B�b�N�̔ԍ�
	typedef enum
	{
		STICKTYPE_LEFT = 0, // ���X�e�B�b�N
		STICKTYPE_RIGHT, // �E�X�e�B�b�N
		STICKTYPE_MAX
	}STICKTYPE;

	//�X�e�B�b�N�̕���
	typedef enum
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	}STICKANGLE;

	//�X�e�B�b�N�̓��͏��
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
		float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
	}STICKINPUT;

	CInputGamepad();
	~CInputGamepad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;
	bool GetJoypadPress(JOYKEY key);
	bool GetJoypadTrigger(JOYKEY key);
	bool GetJoypadRepeat(JOYKEY key);
	XINPUT_STATE* GetXInputState(void);
	void UpdateStick(XINPUT_STATE* stickstate);
	STICKINPUT GetStick(void);
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

	float GetJoyLX();
	float GetJoyLY();
	D3DXVECTOR2 GetRTrigger() { return m_R_Trigger; }
	D3DXVECTOR2 GetLTrigger() { return m_L_Trigger; }

	//float GetPadthumb(float padLX, float padLY, float padRX, float padRY);
private:
	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];

	WORD m_joyKeyState;
	WORD m_joyKeyStateTrigger;
	WORD m_ajoyKeyStateRelease;
	WORD m_aJoypadCurrentTime;
	WORD m_aJoypadExecLastTime;
	WORD m_JoypadInput;
	D3DXVECTOR3 m_joyStickPos;
	D3DXVECTOR2 m_R_Trigger;
	D3DXVECTOR2 m_L_Trigger;
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX];
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX];
	STICKINPUT m_stick;
	XINPUT_STATE m_XInput;
	XINPUT_VIBRATION m_JoypadMotor;
};
#endif