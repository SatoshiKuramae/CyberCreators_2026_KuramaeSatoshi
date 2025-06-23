//==============================================================
//
// explosion.h
//
//==============================================================
#include "explosion.h"
#include "manager.h"

//静的メンバ初期化
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion = nullptr;

//コンストラクタ
CExplosion::CExplosion()
{
	
}
//デストラクタ
CExplosion::~CExplosion()
{

}

//初期化
HRESULT CExplosion::Init()
{

	CObject2D::Init();

	return S_OK;
}

//終了処理
void CExplosion::Uninit()
{
	CObject2D::Uninit();
	////テクスチャの破棄
	//if (m_pTextureExplosion != nullptr)
	//{
	//	m_pTextureExplosion->Release();
	//	m_pTextureExplosion = nullptr;
	//}

	////頂点バッファの破棄
	//if (m_pVtxBuffExplosion != nullptr)
	//{
	//	m_pVtxBuffExplosion->Release();
	//	m_pVtxBuffExplosion = nullptr;
	//}
}

//更新処理
void CExplosion::Update()
{
	CObject2D::Update();
	//VERTEX_2D* pVtx;
	//m_Explosion->nCounterAnim++;
	//if (m_Explosion->nCounterAnim == 5)
	//{
	//	m_Explosion->nCounterAnim = 0;
	//	m_Explosion->nPatternAnim++;
	//	if (m_Explosion->nPatternAnim >= 8)
	//	{
	//		Release();
	//	}
	//	//頂点バッファをロックし、頂点データへのポインタを取得
	//	m_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	//	pVtx[0].tex.x += EXPLOSION_TX_X;
	//	pVtx[1].tex.x += EXPLOSION_TX_X;
	//	pVtx[2].tex.x += EXPLOSION_TX_X;
	//	pVtx[3].tex.x += EXPLOSION_TX_X;
	//	//頂点バッファをアンロック
	//	m_pVtxBuffExplosion->Unlock();
	//}
}

//描画処理
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//CExplosion生成
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion();
	//テクスチャの生成
	pExplosion->BindTexture(m_pTextureExplosion, D3DXVECTOR2(8, 1));
	pExplosion->Setpos(pos);
	pExplosion->SetParam(300, 300);
	pExplosion->Init();
	
	

	return pExplosion;
}

//ロード
HRESULT CExplosion::Load()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTextureExplosion == nullptr)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, "texture\\explosion000.png", &m_pTextureExplosion);
	}
	return S_OK;
}

//アンロード
void CExplosion::Unload()
{
	if (m_pTextureExplosion != nullptr)
	{
		m_pTextureExplosion->Release();
		m_pTextureExplosion = nullptr;
	}
}