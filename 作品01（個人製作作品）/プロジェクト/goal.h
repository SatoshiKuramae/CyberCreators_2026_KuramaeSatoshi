//============================================================
//
//goal.h
//Author Kuramaesatoshi
//============================================================
#ifndef _CGoal_H_
#define _CGoal_H_
#include "main.h"
#include "objectX.h"

constexpr float GOAL_SIZE_X(40.0f);
constexpr float GOAL_SIZE_Y(40.0f);
constexpr float GOAL_SIZE_Z(40.0f);
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
	D3DXVECTOR3 GetSize() const { return m_Size; }

private:
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_rotGoal;
	D3DXVECTOR3 m_Size = { GOAL_SIZE_X, GOAL_SIZE_Y, GOAL_SIZE_Z };
	// 角度を 0～2π（1回転）以内に収める
	const float m_fTWO_PI = D3DX_PI * 2.0f;
	static LPD3DXMESH m_pMesh_Goal;
	static LPD3DXBUFFER m_pBuffMat_Goal;
	static DWORD m_dwNumMat_Goal;
	static D3DXMATERIAL* m_pMaterial_Goal;
	static LPDIRECT3DTEXTURE9 m_pTexture_Goal;
};
#endif







