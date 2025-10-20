//============================================================
//
//backblock.h
//
//Author Kuramaesatoshi
//============================================================
#ifndef _CBackBlock_H_
#define _CBackBlock_H_
#include "main.h"
#include "objectX.h"
#define NUMTEXTURE (5)
#define NUMBACKBLOCKTYPE (5)


//背景に生成するブロック
class CBackBlock : public CObjectX
{
public:
	typedef enum
	{
		BACKBLOCK_01,
		BACKBLOCK_02,
		BACKBLOCK_03,
		BACKBLOCK_04,
		BACKBLOCK_05,
		BACKBLOCK_MAX,
	}BACKBLOCKTYPE;

	CBackBlock();
	~CBackBlock();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static HRESULT Load();
	static void Unload();
	static CBackBlock* Create(D3DXVECTOR3 pos, BACKBLOCKTYPE BackBlockType ,D3DXVECTOR3  BBlockScale);
	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報などを取得
	void SetBackBlockType(BACKBLOCKTYPE BackBlockType);
	BACKBLOCKTYPE GetBackBlockType();

private:
	D3DXMATRIX m_mtxWorld;
	BACKBLOCKTYPE m_BackBlockType;

	static LPD3DXMESH m_pMesh_BackBlock[NUMBACKBLOCKTYPE];
	static LPD3DXBUFFER m_pBuffMat_BackBlock[NUMBACKBLOCKTYPE];
	static DWORD m_dwNumMat_BackBlock[NUMBACKBLOCKTYPE];
	static D3DXMATERIAL* m_pMaterial_BackBlock;
	
};
#endif







