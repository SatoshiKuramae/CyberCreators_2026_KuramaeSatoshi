//==============================================================
//
// bullet.cpp
//
// Author:Satoshi Kuramae
//==============================================================
#include "bullet.h"
#include "manager.h"
#include "explosion.h"

LPDIRECT3DTEXTURE9 CBullet::m_pTexturebullet = nullptr;


//コンストラクタ
CBullet::CBullet(int nPriority) :CObject2D(nPriority)
{
	CBullet::m_Bulletlife = 0;
}

//デストラクタ
CBullet::~CBullet()
{

}

HRESULT CBullet::Init()
{
	CObject::SetType(TYPE::BULLET);
	CObject2D::Init();
	return S_OK;
}

void CBullet::Uninit()
{
	CObject2D::Uninit();
}

void CBullet::Draw()
{
	CObject2D::Draw();
}

void CBullet::Update()
{
	m_posPolygon.x += m_move.x;
	m_posPolygon.y += m_move.y;

	CObject2D::Update();

	m_Bulletlife++;
	if (m_Bulletlife >= 50)
	{
		GetPos();
		m_Bulletlife = 0;
		CObject::Release();
		CExplosion::Create(GetPos());
	}
	//for (int i = 0; i < MAX_BULLET; i++)
	//{
	//	CObject* pObj = CObject::GetObject(i, 2);
	//	if (pObj != nullptr)
	//	{
	//		CObject::TYPE type = pObj->GetType();
	//		if (type == CObject::TYPE::ENEMY)
	//		{
	//			CollisionEnemy(m_posPolygon);
	//		}
	//		else if (type == CObject::TYPE::PLAYER)
	//		{
	//			CollisionPlayer(m_posPolygon);
	//		}
	//	}
	//	
	//}
}
//
////弾と敵の当たり判定
//bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
//{
//
//}
//
////弾とプレイヤーの当たり判定
//bool CBullet::CollisionPlayer(D3DXVECTOR3 pos)
//{
//
//}

//Cbullet生成
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	CBullet* pBullet = new CBullet();
	//テクスチャの生成
	pBullet->BindTexture(m_pTexturebullet,D3DXVECTOR2(1,1));
	pBullet->SetParam(50.0f, 50.0f);
	pBullet->Setpos(pos);
	pBullet->SetMove(move);
	pBullet->Init();
	return pBullet;
}

void CBullet::Setpos(D3DXVECTOR3 pos)
{
	m_posPolygon = pos;
}

HRESULT CBullet::Load()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTexturebullet == nullptr)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, "texture\\bullet000.png", &m_pTexturebullet);
	}
	return S_OK;
}

//アンロード
void CBullet::Unload()
{
	if (m_pTexturebullet != nullptr)
	{
		m_pTexturebullet->Release();
		m_pTexturebullet = nullptr;
	}
}

