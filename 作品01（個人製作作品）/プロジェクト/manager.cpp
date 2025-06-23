//==============================================================
//
// manager.cpp
//
//==============================================================

#include<Windows.h>
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "bg.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "floor.h"
#include "objectX.h"
#include "player.h"
#include "block.h"
#include "background.h"
#include "backblock.h"

//静的メンバ初期化
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CInputGamepad* CManager::m_pJoypad = nullptr;
//CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CFade* CManager::m_pFade = nullptr;
CModel* CManager::m_pModel = nullptr;
CSound* CManager::m_pSound = nullptr;
CGameprogress* CManager::m_pGameState = new CGameprogress();

//コンストラクタ
CManager::CManager()
{

}
//デストラクタ
CManager::~CManager()
{

}

//初期化
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pScene = new CScene();
	m_pScene->Init();
	//レンダラーの生成
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	//キーボードの生成
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	// ジョイパッドの生成
	m_pJoypad = new CInputGamepad();
	m_pJoypad->Init(hInstance, hWnd);

	//カメラ生成
	/*m_pCamera = new CCamera();
	m_pCamera->Init();*/

	//ライト生成
	m_pLight = new CLight();
	m_pLight->Init();

	//テクスチャの生成
	m_pTexture = new CTexture();

	//モデルの生成
	m_pModel = new CModel();

	//サウンド初期化
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	m_pFade = new CFade();
	m_pFade->Init();

	

	//上から順に描画される
	CBg::Load();
	CBackBlock::Load();
	CPlayer::Load();
	CBlock::Load();
	CEnemy::Load();
	CExplosion::Load();
	CBullet::Load();
	CFloor::Load();

	//最初のシーンの設定

	m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	
	
	return S_OK;
}

//終了処理
void CManager::Uninit()
{
	CBg::Unload();
	CBackBlock::Unload();
	CEnemy::Unload();
	CBlock::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CFloor::Unload();
	
	CTexture::Unload();
	CModel::Unload();
	if (m_pRenderer != nullptr)
	{
		m_pScene->Uninit();
		m_pKeyboard->Uninit();
		m_pRenderer->Uninit();
		m_pJoypad->Uninit();
		m_pFade->Uninit();
		m_pSound->Uninit();
		m_pTexture->Unload();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	CObject::ReleaseAll();
}

//更新処理
void CManager::Update()
{
	m_pRenderer->Update();
	m_pScene->Update();
	m_pKeyboard->Update();
	m_pJoypad->Update();
	//m_pCamera->Update();
	m_pFade->Update();
}

//描画処理
void CManager::Draw()
{
	m_pRenderer->Draw();
	m_pFade->Draw();
	m_pScene->Draw();
}

void CManager::SetMode(CScene::MODE mode)
{
	//終了処理
	if (m_pScene != nullptr)
	{
		//m_pCamera->Init();
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (mode == CScene::MODE::MODE_TITLE)
	{
		m_pGameState->Reset();
	}

	CObject::ReleaseAll();
	//生成
	m_pScene = CScene::Create(mode);
}

//レンダラー取得
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//キーボード取得
CInputKeyboard* CManager::GetKeyboard(){
	return m_pKeyboard;
}

//ジョイパッド取得
CInputGamepad* CManager::GetJoypad(){
	return m_pJoypad;
}
//カメラの取得
//CCamera* CManager::GetCamera()
//{
//	return m_pCamera;
//}

//ライトの取得
CLight* CManager::GetLight()
{
	return m_pLight;
}

//シーンの取得
CScene* CManager::GetScene()
{
	return m_pScene;
}

CTexture* CManager::GetTexture() 
{
	return m_pTexture;
}

CFade* CManager::GetFade()
{
	return m_pFade;
}

CModel* CManager::GetModel()
{
	return m_pModel;
}

CSound* CManager::GetSound()
{
	return m_pSound;
}

CGameprogress* CManager::GetGameProgress() {
	return m_pGameState;
}