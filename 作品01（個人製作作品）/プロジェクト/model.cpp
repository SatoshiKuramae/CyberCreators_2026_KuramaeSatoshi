//===============================================================================
//
// model.cpp
// 
//===============================================================================
#include "model.h"
#include "manager.h"

CModel::MODELINFO CModel::m_ModelInfo[NUMMODEL] = {};
std::string CModel::m_pModelName[NUMMODEL];

//コンストラクタ
CModel::CModel()
{
	
}

//デストラクタ
CModel::~CModel()
{

}

//モデル破棄
void CModel::Unload()
{
	for (int i = 0; i < NUMMODEL; i++)
	{
		if (m_ModelInfo->m_Mesh_Model != nullptr)
		{
			m_ModelInfo->m_Mesh_Model->Release();
			m_ModelInfo->m_Mesh_Model = nullptr;
		}
		if (m_ModelInfo->m_Buff_Model != nullptr)
		{
			m_ModelInfo->m_Buff_Model->Release();
			m_ModelInfo->m_Buff_Model = nullptr;
		}
	}
}

//登録
int CModel::Regist(const char* pModelName)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx = 0;	//ID

	for (int i = 0; i < NUMMODEL; i++)
	{
		if (m_ModelInfo[i].m_Mesh_Model == nullptr)
		{//登録されていない
			m_pModelName[i] = pModelName;
			//Xファイルの読み込み
			D3DXLoadMeshFromX(pModelName,
				D3DXMESH_SYSTEMMEM, pDevice,
				NULL,
				&m_ModelInfo[i].m_Buff_Model,
				NULL,
				&m_ModelInfo[i].m_dwNumMat_Model,
				& m_ModelInfo[i].m_Mesh_Model);

			nIdx = i;		//ID設定
			break;
		}
		else if (strcmp(pModelName, m_pModelName[i].c_str()) == 0)
		{//同じだったら
			nIdx = i;
			break;
		}
	}
	return nIdx;
}

CModel::MODELINFO CModel::GetAddress(int nIdx)
{
	return m_ModelInfo[nIdx];
}