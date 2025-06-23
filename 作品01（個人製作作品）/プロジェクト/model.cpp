//===============================================================================
//
// model.cpp
// 
//===============================================================================
#include "model.h"
#include "manager.h"

CModel::MODELINFO CModel::m_ModelInfo[NUMMODEL] = {};
std::string CModel::m_pModelName[NUMMODEL];

//�R���X�g���N�^
CModel::CModel()
{
	
}

//�f�X�g���N�^
CModel::~CModel()
{

}

//���f���j��
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

//�o�^
int CModel::Regist(const char* pModelName)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx = 0;	//ID

	for (int i = 0; i < NUMMODEL; i++)
	{
		if (m_ModelInfo[i].m_Mesh_Model == nullptr)
		{//�o�^����Ă��Ȃ�
			m_pModelName[i] = pModelName;
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(pModelName,
				D3DXMESH_SYSTEMMEM, pDevice,
				NULL,
				&m_ModelInfo[i].m_Buff_Model,
				NULL,
				&m_ModelInfo[i].m_dwNumMat_Model,
				& m_ModelInfo[i].m_Mesh_Model);

			nIdx = i;		//ID�ݒ�
			break;
		}
		else if (strcmp(pModelName, m_pModelName[i].c_str()) == 0)
		{//������������
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