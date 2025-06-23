//============================================================
//
//goal.h
//Author Kuramaesatoshi
//============================================================
#ifndef _CGoal_H_
#define _CGoal_H_
#include "main.h"
#include "objectX.h"


//ゴールクラス
class CGoal : public CObjectX
{
public:

	CGoal();
	~CGoal();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	HRESULT Load();
	void Unload();
	static CGoal* Create(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報などを取得


private:
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_rotGoal;		//角度
	static LPD3DXMESH m_pMesh_Goal;
	static LPD3DXBUFFER m_pBuffMat_Goal;
	static DWORD m_dwNumMat_Goal;
	static D3DXMATERIAL* m_pMaterial_Goal;
	static LPDIRECT3DTEXTURE9 m_pTexture_Goal;
};
#endif







