//===============================================================================
//
//model.cpp
//Author Kuramaesatoshi
//===============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include <iostream>
#include <string>
#define NUMMODEL (12)
//XÉtÉ@ÉCÉãä«óù

class CModel
{
public:
	typedef struct
	{
		LPD3DXMESH m_Mesh_Model;
		LPD3DXBUFFER m_Buff_Model;
		DWORD m_dwNumMat_Model;
	}MODELINFO;

	CModel();
	~CModel();
	static void Unload();
	int Regist(const char* pFileName);
	MODELINFO GetAddress(int nIdx);
private:

	static std::string m_pModelName[NUMMODEL];
	static MODELINFO m_ModelInfo[NUMMODEL];
};
#endif
