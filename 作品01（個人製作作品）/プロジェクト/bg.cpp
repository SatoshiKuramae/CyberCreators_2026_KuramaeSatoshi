
//===============================================================================
//
//各画面の背景
// 
//===============================================================================
#include "main.h"
#include "bg.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "background.h"

int CBg::m_pTextureBg = 0;
//コンストラクタ
CBg::CBg(int nPriority) :CObject2D(nPriority)
{

}

//デストラクタ
CBg::~CBg()
{

}

//初期化（頂点バッファ生成）
HRESULT CBg::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;
	
	if (pScene->GetScene() == CScene::MODE_TITLE)
	{
		m_pTextureBg = pTex->Regist("data\\texture\\title.png");
	}
	else if (pScene->GetScene() == CScene::MODE_SELECT)
	{
		m_pTextureBg = pTex->Regist("data\\texture\\stageselect.png");
	}
	else if (pScene->GetScene() == CScene::MODE_GAME|| pScene->GetScene() == CScene::MODE_TUTORIAL)
	{
		m_pTextureBg = pTex->Regist("data\\texture\\game.png");
	}
	else if (pScene->GetScene() == CScene::MODE_RESULT_CLEAR)
	{
		m_pTextureBg = pTex->Regist("data\\texture\\result_clear.png");
	}
	else if (pScene->GetScene() == CScene::MODE_RESULT_GAMEOVER)
	{
		m_pTextureBg = pTex->Regist("data\\texture\\result_gameover.png");
	}

	CObject2D::BindTexture(pTex->GetAddress(m_pTextureBg), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	return S_OK;
}

//終了(頂点バッファ破棄)
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//更新処理(頂点バッファの更新)
void CBg::Update()
{
	CObject2D::Update();
}

//描画（ポリゴン描画）
void CBg::Draw()
{
	CObject2D::Draw();
}


//Object2D生成
CBg* CBg::Create(D3DXVECTOR3 pos)
{
	CBg* pBg = new CBg;
	pBg->Setpos(pos);
	pBg->SetParam(SCREEN_WIDTH, SCREEN_HEIGHT);
	pBg->Init();
	pBg->SetAnim(0.0f, 1.0f);
	return pBg;
}


//ロード
HRESULT CBg::Load()
{	
	return S_OK;
}

//アンロード
void CBg::Unload()
{
	
}