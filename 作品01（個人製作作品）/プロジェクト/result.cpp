//===============================================================================
//
// result.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "result.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "bg.h"


CResult* m_pTime_Result = nullptr;
CSound* m_pSound_Result = nullptr;
CResultrank* m_pResultrank = nullptr;

//コンストラクタ
CResult::CResult() 
{

}
//デストラクタ
CResult::~CResult() 
{

}

//初期化処理
HRESULT CResult::Init() 
{
	CScene* pScene = nullptr;

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(CLEAR_RESULTUI_POS);
	
	if (m_pTime_Result == nullptr)
	{
		m_pTime_Result = new CTime;
		m_pTime_Result->Init();
	}

	if (pScene->GetScene() != CScene::MODE_RESULT_GAMEOVER)
	{
		m_pResultrank->Create(RESULTRANK_UI_POS);
	}
	 
	m_pSound_Result = CManager::GetSound();

	m_pSound_Result->PlaySound(CSound::SOUND_LABEL_BGM_01);
	
	return S_OK;
}

//終了処理
void CResult::Uninit()
{

	m_pTime_Result->Uninit();
	if (m_pResultrank != nullptr)
	{
		m_pResultrank->Uninit();
	}
	if (m_pBg) 
	{
		m_pBg->Uninit();
	}
	m_pSound_Result->StopSound();
}

//更新処理
void CResult::Update() 
{

	m_pTime_Result->ResultTimer();
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();

	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A) == true)
	{
		m_pSound_Result->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_TITLE);
	}
#ifdef DEBUG

	if (pKeyboard->GetKeyboardTrigger(DIK_R) == true)
	{
		m_pSound_Result->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_GAME);
	}
#endif // !DEBUG

}

//描画処理
void CResult::Draw()
{

}