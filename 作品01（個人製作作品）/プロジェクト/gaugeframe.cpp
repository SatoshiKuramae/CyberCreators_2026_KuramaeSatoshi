
//===============================================================================
//
//ゲージフレーム
// gaugeflame.cpp
// Author:Satoshi Kuramae
//===============================================================================
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "gaugeframe.h"


//コンストラクタ
CGaugeframe::CGaugeframe(int nPriority) :CObject2D(nPriority)
{

}

//デストラクタ
CGaugeframe::~CGaugeframe()
{

}

//初期化（頂点バッファ生成）
HRESULT CGaugeframe::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;

	m_pTextureGaugeframe = pTex->Regist("data\\texture\\gaugeframe.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTextureGaugeframe), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	
	return S_OK;
}

//終了(頂点バッファ破棄)
void CGaugeframe::Uninit()
{
	CObject2D::Uninit();
}

//更新処理(頂点バッファの更新)
void CGaugeframe::Update()
{
	CObject2D::Update();
}

//描画（ポリゴン描画）
void CGaugeframe::Draw()
{
	CObject2D::Draw();
}

//生成
CGaugeframe* CGaugeframe::Create(D3DXVECTOR3 pos)
{
	CGaugeframe* pCGaugeframe = new CGaugeframe;
	pCGaugeframe->Setpos(pos);
	pCGaugeframe->SetParam(480.0f, 150.0f);
	pCGaugeframe->Init();
	pCGaugeframe->SetAnim(0.0f, 1.0f);

	return pCGaugeframe;
}
