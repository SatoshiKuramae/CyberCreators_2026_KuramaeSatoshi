
//===============================================================================
//
//ゲージフレーム
// 
//===============================================================================
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "gauge.h"


//コンストラクタ
CGauge::CGauge(int nPriority) :CObject2D(nPriority)
{

}

//デストラクタ
CGauge::~CGauge()
{

}

//初期化（頂点バッファ生成）
HRESULT CGauge::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;

	m_pTextureGauge = pTex->Regist("data\\texture\\gauge.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTextureGauge), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	
	return S_OK;
}

//終了(頂点バッファ破棄)
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//更新処理(頂点バッファの更新)
void CGauge::Update()
{
	// アビリティゲージの値を取得（例: 0～100）
	float gauge = CManager::GetGameProgress()->GetAbilityGauge();

	// 最大値で割って-1.0～1.0に変換
	float rate = static_cast<float>(gauge) / 100;
	float rateM11 = rate * 2.0f - 1.0f;
	
	// ゲージ長さを更新
	SetRate(rateM11);
	CObject2D::Update();
}

//描画（ポリゴン描画）
void CGauge::Draw()
{
	CObject2D::Draw();
}

//生成
CGauge* CGauge::Create(D3DXVECTOR3 pos)
{
	CGauge* pCGauge = new CGauge;
	pCGauge->Setpos(pos);
	pCGauge->SetParam(420.0f, 100.0f);
	pCGauge->Init();
	pCGauge->SetAnim(0.0f, 1.0f);

	return pCGauge;
}


void CGauge::SetRate(float rate)
{
	// rate は 0.0f ～ 1.0f の値にする（例: ゲージ50% → 0.5f）

	if (rate < -1.0f) {
		rate = -1.0f;
	}
	else if (rate > 1.0f) {
		rate = 1.0f;
	}
	SetLengthPolygon(rate);
}