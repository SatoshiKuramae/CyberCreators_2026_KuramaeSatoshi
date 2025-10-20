//============================================================
//
//item.h
//Author Kuramaesatoshi
//============================================================
#ifndef _CITEM_H_
#define _CITEM_H_
#include "main.h"
#include "objectX.h"

constexpr float  ROTSPEED(0.1f);
constexpr float ITEM_SIZE_X(40.0f);
constexpr float ITEM_SIZE_Y(40.0f);
constexpr float ITEM_SIZE_Z(40.0f);

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
	D3DXVECTOR3 GetSize() const { return m_Size; }

private:
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_Size = { ITEM_SIZE_X, ITEM_SIZE_Y, ITEM_SIZE_Z };

	static LPD3DXMESH m_pMesh_Item;
	static LPD3DXBUFFER m_pBuffMat_Item;
	static DWORD m_dwNumMat_Item;
	static D3DXMATERIAL* m_pMaterial_Item;
};
#endif







