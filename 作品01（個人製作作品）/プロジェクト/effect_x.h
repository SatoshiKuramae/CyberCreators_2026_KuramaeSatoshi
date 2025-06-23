//============================================================
//
//effect.h
//
//Author Kuramaesatoshi
//============================================================
#ifndef _Effect_H_
#define _Effect_H_
#include "objectX.h"
class CEffect_X :public CObjectX
{
public:

	CEffect_X();
	~CEffect_X();
	HRESULT Init();
	void Uninit();
	void Draw();
	void Update();
	static CEffect_X* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* filename);
private:
	float m_fRGBColor;
	const char* m_filename;
	int m_Life;
	static LPD3DXMESH m_pMesh_Effect;
	static LPD3DXBUFFER m_pBuffMat_Effect;
	static DWORD m_dwNumMat_Effect;
	static D3DXMATERIAL* m_pMaterial_Effect;
	float m_fScale;

};
#endif