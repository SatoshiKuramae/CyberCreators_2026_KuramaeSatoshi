//===============================================================================
//
//texture.cpp
// 
//===============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"
#include <iostream>
#include <string>
#include "texture.h"

constexpr int NUMTEX = 20;

//テクスチャ管理
class CTexture
{
public:
	CTexture();
	~CTexture();
	static void Unload();
	int Regist(const char* pTextureName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[NUMTEX];
	static std::string m_pTextureName[NUMTEX];
	static int m_NumTexture;
};
#endif