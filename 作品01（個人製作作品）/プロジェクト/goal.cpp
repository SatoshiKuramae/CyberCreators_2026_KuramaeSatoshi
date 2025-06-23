//===============================================================================
//
//Goal.cpp
// 
// Author:Satoshi Kuramae
//===============================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "goal.h"
LPD3DXMESH CGoal::m_pMesh_Goal=nullptr;
LPD3DXBUFFER CGoal::m_pBuffMat_Goal=nullptr;
DWORD CGoal::m_dwNumMat_Goal = NULL;
D3DXMATERIAL* CGoal::m_pMaterial_Goal = nullptr;


//コンストラクタ
CGoal::CGoal()
{

}

//デストラクタ
CGoal::~CGoal()
{

}

//初期化処理
HRESULT CGoal::Init()
{
	m_rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE::GOAL);
	CGoal::Load();
	//モデルテクスチャの読み込み
	CObjectX::Init();


	return S_OK;
}

//終了処理
void CGoal::Uninit()
{
	CObjectX::Uninit();
}

//更新処理
void CGoal::Update()
{
	m_rotGoal.z+=0.08f;
	m_rotGoal.y+=0.02f;
	m_rotGoal.x+=0.05f;
	SetRot(m_rotGoal);
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 pos;
	pos = GetPos();
	Setpos(pos);
	CObjectX::Update();
}

//描画処理
void CGoal::Draw()
{
	CObjectX::Draw();
}

//ロード処理
HRESULT CGoal::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\xfile\\goal.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Goal,
		NULL,
		&m_dwNumMat_Goal,
		&m_pMesh_Goal);

	return S_OK;
}


//アンロード
void CGoal::Unload()
{
	//メッシュの破棄
	if (CGoal::m_pMesh_Goal != nullptr)
	{
		CGoal::m_pMesh_Goal->Release();
		CGoal::m_pMesh_Goal = NULL;
	}
	//マテリアルの破棄
	if (CGoal::m_pBuffMat_Goal != NULL)
	{
		CGoal::m_pBuffMat_Goal->Release();
		CGoal::m_pBuffMat_Goal = NULL;
	}
}

//生成
CGoal* CGoal::Create(D3DXVECTOR3 pos)
{
	CGoal* pObject3D = new CGoal;

	pObject3D->Init();
	pObject3D->Setpos(pos);
	
	pObject3D->BindMesh(m_pMesh_Goal, m_pBuffMat_Goal, m_dwNumMat_Goal, m_pMaterial_Goal, nullptr);
	

	pObject3D->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	return pObject3D;
}
