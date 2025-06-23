//===============================================================================
//
// result.cpp
// 
//===============================================================================
#include "result.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "bg.h"


CResult* m_pTime_Result = nullptr;
CSound* m_pSound_Result = nullptr;
CResultrank* m_pResultrank = nullptr;


CResult::CResult() {

}

CResult::~CResult() {

}

//‰Šú‰»ˆ—
HRESULT CResult::Init() {
	CScene* pScene = nullptr;

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(D3DXVECTOR3(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f));
	
	if (m_pTime_Result == nullptr)
	{
		m_pTime_Result = new CTime;
		m_pTime_Result->Init();
	}

	if (pScene->GetScene() != CScene::MODE_RESULT_GAMEOVER)
	{
		m_pResultrank->Create(D3DXVECTOR3(MAXPOS_X / 2, MAXPOS_Y / 2 - 70.0f, 0.0f));
	}
	 
	m_pSound_Result = CManager::GetSound();

	m_pSound_Result->PlaySound(CSound::SOUND_LABEL_BGM_01);
	
	return S_OK;
}

//I—¹ˆ—
void CResult::Uninit() {

	m_pTime_Result->Uninit();
	if (m_pResultrank != nullptr)
	{
		m_pResultrank->Uninit();
	}
	if (m_pBg) {
		m_pBg->Uninit();
	}
	m_pSound_Result->StopSound();
}

//XVˆ—
void CResult::Update() {

	m_pTime_Result->ResultTimer();
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();

	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A) == true)
	{
		m_pSound_Result->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_TITLE);
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_R) == true)
	{
		m_pSound_Result->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_GAME);
	}
}

//•`‰æˆ—
void CResult::Draw() {

}