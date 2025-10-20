//===============================================================================
//
// game.cpp
// Author:Satoshi Kuramae
// 
//===============================================================================
#include "game.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "block.h"
#include "floor.h"
#include "goal.h"
#include "backblock.h"
#include "stageselect.h"
#include "time.h"
#include "bg.h"
#include "item.h"

bool meshuse;

CGame* m_pTime = nullptr;
CGame* m_pNumplayer = nullptr;
CSound* m_pSound_Game = nullptr;

//コンストラクタ
CGame::CGame() {
	m_bPouse = false;
}

//デストラクタ
CGame::~CGame() {

}

//初期化処理
HRESULT CGame::Init() 
{
	meshuse = false;
	m_bPouse = false;
	m_pSound_Game = CManager::GetSound();
	if (m_pTime == nullptr && m_pNumplayer == nullptr)
	{
		m_pTime = new CTime;
		m_pNumplayer = new CNumplayer;
	}

	m_pTime->Init();

	m_pCamera = new CCamera();
	m_pCamera->Init();  // 各シーンごとに初期化

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(GAMEUI_POS);


	//選択されているステージに対応した曲を流す
	if (CStageselect::GetStageSelect() == 1)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_01);
		m_filePath = STAGE1;
	}
	if (CStageselect::GetStageSelect() == 2)
	{
		m_filePath = STAGE2;
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_02);
	}
	if (CStageselect::GetStageSelect() == 3)
	{
		m_filePath = STAGE3;
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_03);
	}
	if (CStageselect::GetStageSelect() == 4)
	{
		m_filePath = STAGE4;
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_04);
	}
	if (CStageselect::GetStageSelect() == 5)
	{
		m_filePath = STAGE5;
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_05);
	}

	Load();


	m_pNumplayer->Init();

	m_pGauge = new CGauge();
	m_pGaugeframe = new CGaugeframe();

	m_pGauge->Init();
	m_pGaugeframe->Init();

	m_pGauge->Create(GAUGE_POS);
	m_pGaugeframe->Create(GAUGEFLAME_POS);

	

	return S_OK;
}

//終了処理
void CGame::Uninit() {

	m_pSound_Game->StopSound();
	m_pTime->Uninit();
	m_pNumplayer->Uninit();

	if (m_pCamera != nullptr) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pBg) {
		m_pBg->Uninit();
	}

	m_pGauge->Uninit();
	m_pGaugeframe->Uninit();
}

//更新処理
void CGame::Update() 
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	m_pTime->Update();
	
	m_pCamera->SetCamera();
	m_pCamera->Update();

	CPlayableScene::Update();

	m_pNumplayer->Update();
	m_pGauge->Update();


#ifndef DEBUG
	if (pKeyboard->GetKeyboardPress(DIK_P) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_RESULT_CLEAR);
	}
#endif // !DEBUG
}

//描画処理
void CGame::Draw() {
	CPlayableScene::Draw();
	m_pGauge->Draw();
	m_pGaugeframe->Draw();
}

//ステージの生成処理
void CGame::Load()
{
	LoadStage(m_filePath);
}

void CGame::GetPause(bool bPause)
{
	bPause = m_bPouse;
}
