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

//コンストラクタ
CTexture::CTexture()
{
	//各メンバの初期化
	CTexture::m_NumTexture = 0;
}

//デストラクタ
CTexture::~CTexture()
{

}

//テクスチャ破棄
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

//テクスチャ登録
int CTexture::Regist(const char* pTextureName)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx = 0;	//テクスチャID

	for (int i = 0; i < NUMTEX; i++)
	{
		if (m_pTexture[i] == nullptr)
		{//登録されていない
			m_pTextureName[i] = pTextureName;
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_pTexture[i]);
			nIdx = i;		//ID設定
			m_NumTexture++;	//テクスチャ
			break;
		}
		else if (strcmp(pTextureName, m_pTextureName[i].c_str()) == 0)
		{//同じだったら
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