//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���{�S��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"
#include "xaudio2.h"
//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
class CSound
{
public:

	typedef enum
	{
		//BGM
		SOUND_LABEL_BGM_00 = 0,
		SOUND_LABEL_BGM_01,
		SOUND_LABEL_GAMEBGM_01,
		SOUND_LABEL_GAMEBGM_02,
		SOUND_LABEL_GAMEBGM_03,
		SOUND_LABEL_GAMEBGM_04,
		SOUND_LABEL_GAMEBGM_05,
		//���ʉ�
		SOUND_LABEL_JUMP,		//�W�����v
		SOUND_LABEL_LOWJUMP,
		SOUND_LABEL_HIGHJUMP,
		SOUND_LABEL_POWERUP,
		SOUND_LABEL_CLICK,
		SOUND_LABEL_CHOICE,
		SOUND_LABEL_WARNING,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:

	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	typedef struct
	{
		const char* m_pFilename;	// �t�@�C����
		int m_nCntLoop;			// ���[�v�J�E���g
		float m_fVolume;			//����
	} SOUNDINFO;

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		//BGM
		{"data/bgm/bgm01.wav", 0,1.0f},
		{"data/bgm/bgm02.wav", 0,1.0f},
		{"data/bgm/gamebgm01.wav", 0,1.0f},
		{"data/bgm/gamebgm02.wav", 0,1.0f},
		{"data/bgm/gamebgm03.wav", 0,1.0f},
		{"data/bgm/gamebgm04.wav", 0,1.0f},
		{"data/bgm/gamebgm05.wav", 0,1.0f},

		//���ʉ�
		{"data/SE/jump.wav", 0,1.0f},
		{"data/SE/lowjump.wav", 0,1.0f},
		{"data/SE/highjump.wav", 0,1.0f},
		{"data/SE/powerup.wav", 0,1.0f},
		{"data/SE/click.wav", 0,0.5f},
		{"data/SE/choice.wav", 0,0.5f},
		{"data/SE/Warning.wav", 0,1.0f},
	};

};


#endif