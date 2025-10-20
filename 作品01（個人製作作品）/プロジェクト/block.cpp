//===============================================================================
//
//block.cpp
// 
// Author:Satoshi Kuramae
//===============================================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "block.h"
LPD3DXMESH CBlock::m_pMesh_Block[TYPE_MAX] = {};
LPD3DXBUFFER CBlock::m_pBuffMat_Block[TYPE_MAX] = {};
DWORD CBlock::m_dwNumMat_Block[TYPE_MAX] = {};
D3DXMATERIAL* CBlock::m_pMaterial_Block = nullptr;
LPDIRECT3DTEXTURE9 CBlock::m_pTexture_Block[NUMTEXTURE] = {};
//コンストラクタ
CBlock::CBlock()
{
	m_movecnt_R, m_movecnt_L = 0;
	m_movechange_R, m_movechange_L = false;
}

//デストラクタ
CBlock::~CBlock()
{

}

//初期化処理
HRESULT CBlock::Init()
{
	CObject::SetType(TYPE::BLOCK);
	CBlock::Load();
	//モデルテクスチャの読み込み
	CObjectX::Init();


	return S_OK;
}

//終了処理
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//更新処理
void CBlock::Update()
{
	CObjectX::Update();
	
	if (m_BlockType == TYPE_MOVE_BLOCK_R)
	{
		m_movecnt_R++;
		if (m_movecnt_R >= 200)
		{
			if (m_movechange_R == false)
			{
				m_movechange_R = true;
				m_move.x = 5.0f;
			}
			else
			{
				m_movechange_R = false;
				m_move.x = -5.0f;
			}
			m_movecnt_R = 0;
		}
	}
	else if (m_BlockType == TYPE_MOVE_BLOCK_L)
	{
		m_movecnt_L++;
		if (m_movecnt_L >= 200)
		{
			if (m_movechange_L == false)
			{
				m_movechange_L = true;
				m_move.x = -5.0f;
			}
			else
			{
				m_movechange_L = false;
				m_move.x = +5.0f;
			}
			m_movecnt_L = 0;
		}

	}
}

//描画処理
void CBlock::Draw()
{
	CObjectX::Draw();
}

//ロード処理
HRESULT CBlock::Load()
{//子クラスで管理するようにしよう
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\xfile\\block_01.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_NOMALBLOCK],
		NULL,
		&m_dwNumMat_Block[TYPE_NOMALBLOCK],
		&m_pMesh_Block[TYPE_NOMALBLOCK]);

	D3DXLoadMeshFromX("data\\xfile\\N_Block.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_N_BLOCK],
		NULL,
		&m_dwNumMat_Block[TYPE_N_BLOCK],
		&m_pMesh_Block[TYPE_N_BLOCK]);
	
	D3DXLoadMeshFromX("data\\xfile\\S_Block.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_S_BLOCK],
		NULL,
		&m_dwNumMat_Block[TYPE_S_BLOCK],
		&m_pMesh_Block[TYPE_S_BLOCK]);
	
	D3DXLoadMeshFromX("data\\xfile\\breakblock.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_BREAK_BLOCK],
		NULL,
		&m_dwNumMat_Block[TYPE_BREAK_BLOCK],
		&m_pMesh_Block[TYPE_BREAK_BLOCK]);


	D3DXLoadMeshFromX("data\\xfile\\moveblock.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_MOVE_BLOCK_R],
		NULL,
		&m_dwNumMat_Block[TYPE_MOVE_BLOCK_R],
		&m_pMesh_Block[TYPE_MOVE_BLOCK_R]);

	D3DXLoadMeshFromX("data\\xfile\\moveblock.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_pBuffMat_Block[TYPE_MOVE_BLOCK_L],
		NULL,
		&m_dwNumMat_Block[TYPE_MOVE_BLOCK_L],
		&m_pMesh_Block[TYPE_MOVE_BLOCK_L]);

	for (int nCntmodel = 0; nCntmodel < NUMTEXTURE; nCntmodel++)
	{
		// モデルのテクスチャファイル
		m_pMaterial_Block = (D3DXMATERIAL*)m_pBuffMat_Block[nCntmodel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat_Block[nCntmodel]; nCntMat++)
		{
			if (m_pMaterial_Block[nCntMat].pTextureFilename != nullptr)
			{ // テクスチャがあるとき
				D3DXCreateTextureFromFile(pDevice, m_pMaterial_Block[nCntMat].pTextureFilename, &m_pTexture_Block[nCntmodel]); // テクスチャを読み込む
			}
		}
	}
	return S_OK;
}


//アンロード
void CBlock::Unload()
{
	for (int i = 0; i < TYPE_MAX; i++)
	{
		//メッシュの破棄
		if (CBlock::m_pMesh_Block[i] != nullptr)
		{
			CBlock::m_pMesh_Block[i]->Release();
			CBlock::m_pMesh_Block[i] = NULL;
		}

		//マテリアルの破棄
		if (CBlock::m_pBuffMat_Block[i] != NULL)
		{
			CBlock::m_pBuffMat_Block[i]->Release();
			CBlock::m_pBuffMat_Block[i] = NULL;
		}
	}
	
}

//生成
CBlock* CBlock::Create(D3DXVECTOR3 pos,BLOCKTYPE BlockType)
{
	CBlock* pObject3D = new CBlock;
	
	pObject3D->Init();
	pObject3D->Setpos(pos);
	pObject3D->SetBlockType(BlockType);
	pObject3D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	for (int i = 0; i < NUMBLOCKTYPE; i++)
	{
		for (int a = 0; a < NUMBLOCKTYPE; a++)
		{
			if (pObject3D->m_BlockType == TYPE_MOVE_BLOCK_R|| pObject3D->m_BlockType == TYPE_MOVE_BLOCK_L)
			{
				if (m_pTexture_Block[a] != nullptr)
				{
					pObject3D->BindMesh(m_pMesh_Block[BlockType], m_pBuffMat_Block[BlockType], m_dwNumMat_Block[BlockType], m_pMaterial_Block, m_pTexture_Block[a]);
				}
				else
				{
					pObject3D->BindMesh(m_pMesh_Block[BlockType], m_pBuffMat_Block[BlockType], m_dwNumMat_Block[BlockType], m_pMaterial_Block, m_pTexture_Block[a]);
				}
			}
			else
			{
				pObject3D->BindMesh(m_pMesh_Block[BlockType], m_pBuffMat_Block[BlockType], m_dwNumMat_Block[BlockType], m_pMaterial_Block, nullptr);
			}
			
		}
	}
	
	pObject3D->SetScale(D3DXVECTOR3(2.4f, 2.4f, 2.4f));
	return pObject3D;
}

//タイプ取得
CBlock::BLOCKTYPE CBlock::GetBlockType()
{
	return m_BlockType;
}

//タイプ取得
void CBlock::SetBlockType(BLOCKTYPE BlockType)
{
	m_BlockType = BlockType;
}