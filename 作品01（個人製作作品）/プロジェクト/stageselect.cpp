//===============================================================================
//
// stageselect.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "game.h"
#include "stageselect.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "block.h"
#include "floor.h"
#include "bg.h"
#include "background.h"
int CStageselect::m_NowSelect = 0;
CSound* m_pSound_Select = nullptr;
CStageselect* m_pTime_Select = nullptr;
int CStageselect::m_nBesttime = 0;

//�R���X�g���N�^
CStageselect::CStageselect() 
{
	m_NowSelect = STAGETITLE;
}

//�f�X�g���N�^
CStageselect::~CStageselect() 
{

}

//����������
HRESULT CStageselect::Init() 
{
	m_pSound_Select = CManager::GetSound();
	m_pSound_Select->PlaySound(CSound::SOUND_LABEL_BGM_00);
	

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(D3DXVECTOR3(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f));
	CCursor::Create(D3DXVECTOR3(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f));
	if (m_pTime_Select == nullptr)
	{
		m_pTime_Select = new CTime;
	}
	m_pTime_Select->Init();

	return S_OK;
}

//�I������
void CStageselect::Uninit() 
{
	if (m_pBg) 
	{
		m_pBg->Uninit();
	}
	m_pSound_Select->StopSound();
	m_pTime_Select->Uninit();
}

//�X�V����
void CStageselect::Update() 
{

	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();

	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_RIGHT) == true)
	{
		m_pSound_Select->PlaySound(CSound::SOUND_LABEL_CHOICE);
		m_NowSelect++;
	}
	else if (pKeyboard->GetKeyboardTrigger(DIK_LEFT) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_LEFT) == true)
	{
		m_pSound_Select->PlaySound(CSound::SOUND_LABEL_CHOICE);
		m_NowSelect--;
	}
	if (m_NowSelect > NUM_STAGE)
	{
		m_NowSelect = 1;
	}
	else if (m_NowSelect <= 0)
	{
		m_NowSelect = NUM_STAGE;
	}

	if (m_NowSelect == 1)
	{
		m_nBesttime = STAGE01_TIME;
		m_pTime_Select->RankTime(m_nBesttime);
	}
	else if (m_NowSelect == 2)
	{
		m_nBesttime = STAGE02_TIME;
		m_pTime_Select->RankTime(m_nBesttime);
	}
	else if (m_NowSelect == 3)
	{
		m_nBesttime = STAGE03_TIME;
		m_pTime_Select->RankTime(m_nBesttime);
	}
	else if (m_NowSelect == 4)
	{
		m_nBesttime = STAGE04_TIME;
		m_pTime_Select->RankTime(m_nBesttime);
	}
	else if (m_NowSelect == 5)
	{
		m_nBesttime = STAGE05_TIME;
		m_pTime_Select->RankTime(m_nBesttime);
	}


	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A) == true)
	{
		m_pSound_Select->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_GAME);
	}
}

//�`�揈��
void CStageselect::Draw() 
{

}

//�I�𒆂̃X�e�[�W�ԍ��擾
int CStageselect::GetStageSelect()
{
	return m_NowSelect;
}

//�X�e�[�W�̍ő��L�^�擾
int CStageselect::GetBestTime()
{
	return m_nBesttime;
}