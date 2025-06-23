//============================================================
//
//goal.h
//Author Kuramaesatoshi
//============================================================
#ifndef _CGoal_H_
#define _CGoal_H_
#include "main.h"
#include "objectX.h"


//�S�[���N���X
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
	D3DXVECTOR3& GetPos() { return m_pos; }	//�ʒu���Ȃǂ��擾


private:
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_rotGoal;		//�p�x
	static LPD3DXMESH m_pMesh_Goal;
	static LPD3DXBUFFER m_pBuffMat_Goal;
	static DWORD m_dwNumMat_Goal;
	static D3DXMATERIAL* m_pMaterial_Goal;
	static LPDIRECT3DTEXTURE9 m_pTexture_Goal;
};
#endif







