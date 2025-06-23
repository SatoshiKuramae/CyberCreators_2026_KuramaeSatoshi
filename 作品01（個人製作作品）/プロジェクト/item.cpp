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

//�R���X�g���N�^
CItem::CItem()
{

}

//�f�X�g���N�^
CItem::~CItem()
{

}

//����������
HRESULT CItem::Init()
{
	CObject::SetType(TYPE::ITEM);
	CItem::Load();
	//���f���e�N�X�`���̓ǂݍ���
	CObjectX::Init();


	return S_OK;
}

//�I������
void CItem::Uninit()
{
	CObjectX::Uninit();
}

//�X�V����
void CItem::Update()
{
	m_rot.y += 0.1f;
	SetRot(m_rot);
	CObjectX::Update();
}

//�`�揈��
void CItem::Draw()
{
	CObjectX::Draw();
}

//���[�h����
HRESULT CItem::Load()
{//�q�N���X�ŊǗ�����悤�ɂ��悤
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\xfile\\item.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Item,
		NULL,
		&m_dwNumMat_Item,
		&m_pMesh_Item);


	return S_OK;
}


//�A�����[�h
void CItem::Unload()
{
	
	//���b�V���̔j��
	if (CItem::m_pMesh_Item != nullptr)
	{
		CItem::m_pMesh_Item->Release();
		CItem::m_pMesh_Item = NULL;
	}

	//�}�e���A���̔j��
	if (CItem::m_pBuffMat_Item != NULL)
	{
		CItem::m_pBuffMat_Item->Release();
		CItem::m_pBuffMat_Item = NULL;
	}
}

//����
CItem* CItem::Create(D3DXVECTOR3 pos)
{
	CItem* pObject3D = new CItem;

	pObject3D->Init();
	pObject3D->Setpos(pos);
	pObject3D->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	pObject3D->BindMesh(m_pMesh_Item, m_pBuffMat_Item, m_dwNumMat_Item, m_pMaterial_Item, nullptr);
	return pObject3D;
}