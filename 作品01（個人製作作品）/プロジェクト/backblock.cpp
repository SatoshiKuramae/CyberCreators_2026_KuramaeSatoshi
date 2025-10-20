//===============================================================================
//
//block.cpp
// 
// Author:Satoshi Kuramae
//===============================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "backblock.h"
LPD3DXMESH CBackBlock::m_pMesh_BackBlock[NUMBACKBLOCKTYPE] = {};
LPD3DXBUFFER CBackBlock::m_pBuffMat_BackBlock[NUMBACKBLOCKTYPE] = {};
DWORD CBackBlock::m_dwNumMat_BackBlock[NUMBACKBLOCKTYPE] = {};
D3DXMATERIAL* CBackBlock::m_pMaterial_BackBlock = nullptr;

//�R���X�g���N�^
CBackBlock::CBackBlock()
{

}

//�f�X�g���N�^
CBackBlock::~CBackBlock()
{

}

//����������
HRESULT CBackBlock::Init()
{
	CObject::SetType(TYPE::BLOCK);
	CBackBlock::Load();

	CObjectX::Init();


	return S_OK;
}

//�I������
void CBackBlock::Uninit()
{
	CObjectX::Uninit();
}

//�X�V����
void CBackBlock::Update()
{
	D3DXVECTOR3 pos;
	pos = GetPos();
	Setpos(pos);
	CObjectX::Update();
}

//�`�揈��
void CBackBlock::Draw()
{
	CObjectX::Draw();
}

//���[�h����
HRESULT CBackBlock::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\xfile\\backblock_01.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_BackBlock[BACKBLOCK_01],
		NULL,
		&m_dwNumMat_BackBlock[BACKBLOCK_01],
		&m_pMesh_BackBlock[BACKBLOCK_01]);

	D3DXLoadMeshFromX("data\\xfile\\backblock_02.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_BackBlock[BACKBLOCK_02],
		NULL,
		&m_dwNumMat_BackBlock[BACKBLOCK_02],
		&m_pMesh_BackBlock[BACKBLOCK_02]);

	D3DXLoadMeshFromX("data\\xfile\\backblock_03.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_BackBlock[BACKBLOCK_03],
		NULL,
		&m_dwNumMat_BackBlock[BACKBLOCK_03],
		&m_pMesh_BackBlock[BACKBLOCK_03]);

	D3DXLoadMeshFromX("data\\xfile\\backblock_04.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_BackBlock[BACKBLOCK_04],
		NULL,
		&m_dwNumMat_BackBlock[BACKBLOCK_04],
		&m_pMesh_BackBlock[BACKBLOCK_04]);
	
	return S_OK;
}


//�A�����[�h
void CBackBlock::Unload()
{
	for (int i = 0; i < NUMBACKBLOCKTYPE; i++)
	{
		//���b�V���̔j��
		if (CBackBlock::m_pMesh_BackBlock[i] != nullptr)
		{
			CBackBlock::m_pMesh_BackBlock[i]->Release();
			CBackBlock::m_pMesh_BackBlock[i] = NULL;
		}

		//�}�e���A���̔j��
		if (CBackBlock::m_pBuffMat_BackBlock[i] != NULL)
		{
			CBackBlock::m_pBuffMat_BackBlock[i]->Release();
			CBackBlock::m_pBuffMat_BackBlock[i] = NULL;
		}
	}

}


//����
CBackBlock* CBackBlock::Create(D3DXVECTOR3 pos, BACKBLOCKTYPE BackBlockType, D3DXVECTOR3 BBlockScale)
{
	CBackBlock* pObjectX = new CBackBlock;

	pObjectX->Init();
	pObjectX->Setpos(pos);
	pObjectX->SetBackBlockType(BackBlockType);

	for (int nCntmodel = 0; nCntmodel < 3; nCntmodel++)
	{
		for (int i = 0; i < (int)m_dwNumMat_BackBlock[nCntmodel]; i++)
		{
			if (m_pMesh_BackBlock[i] != nullptr)
			{
				pObjectX->BindMesh(m_pMesh_BackBlock[BackBlockType], m_pBuffMat_BackBlock[BackBlockType], m_dwNumMat_BackBlock[BackBlockType], m_pMaterial_BackBlock, nullptr);
			}
		}
	}

	pObjectX->SetScale(D3DXVECTOR3(BBlockScale.x, BBlockScale.y, BBlockScale.z));
	return pObjectX;
}

//�^�C�v�擾
CBackBlock::BACKBLOCKTYPE CBackBlock::GetBackBlockType()
{
	return m_BackBlockType;
}

//�^�C�v�擾
void CBackBlock::SetBackBlockType(BACKBLOCKTYPE BlockType)
{
	m_BackBlockType = BlockType;
}