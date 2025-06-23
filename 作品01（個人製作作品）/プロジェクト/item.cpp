//===============================================================================
//
//Item.cpp
// 
//===============================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "item.h"
LPD3DXMESH CItem::m_pMesh_Item = nullptr;
LPD3DXBUFFER CItem::m_pBuffMat_Item = nullptr;
DWORD CItem::m_dwNumMat_Item = {};
D3DXMATERIAL* CItem::m_pMaterial_Item = nullptr;

//コンストラクタ
CItem::CItem()
{

}

//デストラクタ
CItem::~CItem()
{

}

//初期化処理
HRESULT CItem::Init()
{
	CObject::SetType(TYPE::ITEM);
	CItem::Load();
	//モデルテクスチャの読み込み
	CObjectX::Init();


	return S_OK;
}

//終了処理
void CItem::Uninit()
{
	CObjectX::Uninit();
}

//更新処理
void CItem::Update()
{
	m_rot.y += 0.1f;
	SetRot(m_rot);
	CObjectX::Update();
}

//描画処理
void CItem::Draw()
{
	CObjectX::Draw();
}

//ロード処理
HRESULT CItem::Load()
{//子クラスで管理するようにしよう
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\xfile\\item.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Item,
		NULL,
		&m_dwNumMat_Item,
		&m_pMesh_Item);


	return S_OK;
}


//アンロード
void CItem::Unload()
{
	
	//メッシュの破棄
	if (CItem::m_pMesh_Item != nullptr)
	{
		CItem::m_pMesh_Item->Release();
		CItem::m_pMesh_Item = NULL;
	}

	//マテリアルの破棄
	if (CItem::m_pBuffMat_Item != NULL)
	{
		CItem::m_pBuffMat_Item->Release();
		CItem::m_pBuffMat_Item = NULL;
	}
}

//生成
CItem* CItem::Create(D3DXVECTOR3 pos)
{
	CItem* pObject3D = new CItem;

	pObject3D->Init();
	pObject3D->Setpos(pos);
	pObject3D->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	pObject3D->BindMesh(m_pMesh_Item, m_pBuffMat_Item, m_dwNumMat_Item, m_pMaterial_Item, nullptr);
	return pObject3D;
}