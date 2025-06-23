//============================================================
//
//block.h
//
//============================================================
#ifndef _CITEM_H_
#define _CITEM_H_
#include "main.h"
#include "objectX.h"


//3Dオブジェクトクラス
class CItem : public CObjectX
{
public:

	CItem();
	~CItem();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static HRESULT Load();
	static void Unload();
	static CItem* Create(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報などを取得


private:
	D3DXMATRIX m_mtxWorld;
	static LPD3DXMESH m_pMesh_Item;
	static LPD3DXBUFFER m_pBuffMat_Item;
	static DWORD m_dwNumMat_Item;
	static D3DXMATERIAL* m_pMaterial_Item;
};
#endif







