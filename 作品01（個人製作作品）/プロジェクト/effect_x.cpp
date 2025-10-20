//===============================================================================
//
//effect_xcpp
/// Author:Satoshi Kuramae
//
//===============================================================================
#include "effect_x.h"
#include "manager.h"
#include "model.h"

LPD3DXMESH CEffect_X::m_pMesh_Effect = nullptr;
LPD3DXBUFFER CEffect_X::m_pBuffMat_Effect = nullptr;
DWORD CEffect_X::m_dwNumMat_Effect = {};
D3DXMATERIAL* CEffect_X::m_pMaterial_Effect = nullptr;

//コンストラクタ
CEffect_X::CEffect_X()
{
	m_fScale = 2.0f;
	m_fRGBColor = 0;
	m_filename = nullptr;
	m_Life = 0;
}

//デストラクタ
CEffect_X::~CEffect_X()
{

}

//初期化処理
HRESULT CEffect_X::Init()
{
	CObject::SetType(TYPE::EFFECT);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	CModel* pModel = CManager::GetModel();

	int nIdx = pModel->Regist("data\\xfile\\Player_Effect.x");
	pModel->GetAddress(nIdx);
	m_dwNumMat_Effect = pModel->GetAddress(nIdx).m_dwNumMat_Model;
	m_pBuffMat_Effect = pModel->GetAddress(nIdx).m_Buff_Model;
	m_pMesh_Effect = pModel->GetAddress(nIdx).m_Mesh_Model;
	
	CObjectX::Init();
	return S_OK;
}

//終了処理
void CEffect_X::Uninit()
{
	Release();
}

//描画処理
void CEffect_X::Draw()
{
	CObjectX::Draw();
}

//更新処理
void CEffect_X::Update()
{
	m_fScale -= 0.1f;
	CEffect_X::SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));

	m_Life++;
	if (m_Life >= 10)
	{
		m_Life = 0;
		Uninit();
	}
	CObjectX::Update();
}

//生成
CEffect_X* CEffect_X::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename)
{
	CEffect_X* pEffect_X;

	//メモリの確保
	pEffect_X = new CEffect_X;
	pEffect_X->Init();
	
	pEffect_X->CObjectX::GetPos() = pos;
	pEffect_X->CObjectX::GetRot() = rot;

	pEffect_X->m_fRGBColor = 1.0f;
	pEffect_X->m_filename = filename;

	pEffect_X->BindMesh(m_pMesh_Effect, m_pBuffMat_Effect, m_dwNumMat_Effect, m_pMaterial_Effect, nullptr);

	pEffect_X->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	return pEffect_X;
}