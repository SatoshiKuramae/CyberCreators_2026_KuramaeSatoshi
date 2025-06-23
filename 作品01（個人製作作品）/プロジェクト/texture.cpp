//===============================================================================
//
// texture.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "texture.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CTexture::m_pTexture[NUMTEX] = {};
std::string CTexture::m_pTextureName[NUMTEX];
int CTexture::m_NumTexture = 0;

//�R���X�g���N�^
CTexture::CTexture()
{
	//�e�����o�̏�����
	CTexture::m_NumTexture = 0;
}

//�f�X�g���N�^
CTexture::~CTexture()
{

}

//�e�N�X�`���j��
void CTexture::Unload()
{
	for (int i = 0; i < NUMTEX; i++)
	{
		if (m_pTexture[i] != nullptr)
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = nullptr;
		}
	}
}

//�e�N�X�`���o�^
int CTexture::Regist(const char* pTextureName)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx = 0;	//�e�N�X�`��ID

	for (int i = 0; i < NUMTEX; i++)
	{
		if (m_pTexture[i] == nullptr)
		{//�o�^����Ă��Ȃ�
			m_pTextureName[i] = pTextureName;
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_pTexture[i]);
			nIdx = i;		//ID�ݒ�
			m_NumTexture++;	//�e�N�X�`��
			break;
		}
		else if (strcmp(pTextureName, m_pTextureName[i].c_str()) == 0)
		{//������������
			nIdx = i;
			break;
		}
	}
	return nIdx;
}

LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_pTexture[nIdx];
}