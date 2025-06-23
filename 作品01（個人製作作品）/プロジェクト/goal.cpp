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


//�R���X�g���N�^
CGoal::CGoal()
{

}

//�f�X�g���N�^
CGoal::~CGoal()
{

}

//����������
HRESULT CGoal::Init()
{
	m_rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE::GOAL);
	CGoal::Load();
	//���f���e�N�X�`���̓ǂݍ���
	CObjectX::Init();


	return S_OK;
}

//�I������
void CGoal::Uninit()
{
	CObjectX::Uninit();
}

//�X�V����
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

//�`�揈��
void CGoal::Draw()
{
	CObjectX::Draw();
}

//���[�h����
HRESULT CGoal::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\xfile\\goal.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Goal,
		NULL,
		&m_dwNumMat_Goal,
		&m_pMesh_Goal);

	return S_OK;
}


//�A�����[�h
void CGoal::Unload()
{
	//���b�V���̔j��
	if (CGoal::m_pMesh_Goal != nullptr)
	{
		CGoal::m_pMesh_Goal->Release();
		CGoal::m_pMesh_Goal = NULL;
	}
	//�}�e���A���̔j��
	if (CGoal::m_pBuffMat_Goal != NULL)
	{
		CGoal::m_pBuffMat_Goal->Release();
		CGoal::m_pBuffMat_Goal = NULL;
	}
}

//����
CGoal* CGoal::Create(D3DXVECTOR3 pos)
{
	CGoal* pObject3D = new CGoal;

	pObject3D->Init();
	pObject3D->Setpos(pos);
	
	pObject3D->BindMesh(m_pMesh_Goal, m_pBuffMat_Goal, m_dwNumMat_Goal, m_pMaterial_Goal, nullptr);
	

	pObject3D->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	return pObject3D;
}
