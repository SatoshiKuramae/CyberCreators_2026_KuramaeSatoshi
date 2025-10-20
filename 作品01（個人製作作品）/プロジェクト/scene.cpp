//===============================================================================
//
//scene.cpp
// 
//Author Kuramaesatoshi
// 
// TODO ステージ読み込み処理を一つにまとめる、自機を生成するシーン専用のSceneクラスを制定する
//===============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "stageselect.h"
#include "tutorial.h"

CScene::MODE CScene::m_Mode = CScene::MODE_TITLE;

//コンストラクタ
CScene::CScene() 
{

}

//デストラクタ
CScene::~CScene() 
{

}

HRESULT CScene::Init() 
{

	return S_OK;
}

//終了処理
void CScene::Uninit() 
{

}
//更新処理
void CScene::Update() 
{

}
//描画処理
void CScene::Draw()
{

}

//生成
CScene* CScene::Create(MODE mode) 
{

	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle();
		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial();
		break;
	case MODE_SELECT:
		pScene = new CStageselect();
		break;
	case MODE_GAME:
		pScene = new CGame();
		break;
	case MODE_RESULT_CLEAR:
		pScene = new CResult();
		break;
	case MODE_RESULT_GAMEOVER:
		pScene = new CResult();
		break;
	}
	
	m_Mode = mode;
	pScene->Init();
	return pScene;
}

//シーン取得
CScene::MODE CScene::GetScene()
{
	return m_Mode;
}

