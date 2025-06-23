//============================================================
//
//block.h
//
//Author Kuramaesatoshi
//============================================================
#ifndef _CBlock_H_
#define _CBlock_H_
#include "main.h"
#include "objectX.h"
#define NUMTEXTURE (5)
#define NUMBLOCKTYPE (5)
#define JUMP_DEC (2.2f)		//重力

//3Dオブジェクトクラス
class CBlock : public CObjectX
{
public:
	typedef enum
	{
		TYPE_NOMALBLOCK,
		TYPE_S_BLOCK,
		TYPE_N_BLOCK,
		TYPE_BREAK_BLOCK,
		TYPE_MOVE_BLOCK_R,
		TYPE_MOVE_BLOCK_L,
		TYPE_MAX,
	}BLOCKTYPE;

	CBlock();
	~CBlock();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	
	static HRESULT Load();
	static void Unload();
	static CBlock* Create(D3DXVECTOR3 pos, BLOCKTYPE BlockType);
	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報などを取得
	D3DXVECTOR3& GetMove() { return m_move; }
	void SetBlockType(BLOCKTYPE BlockType);
	BLOCKTYPE GetBlockType();

private:
	D3DXMATRIX m_mtxWorld;
	BLOCKTYPE m_BlockType;

	static LPD3DXMESH m_pMesh_Block[TYPE_MAX];
	static LPD3DXBUFFER m_pBuffMat_Block[TYPE_MAX];
	static DWORD m_dwNumMat_Block[TYPE_MAX];
	static D3DXMATERIAL* m_pMaterial_Block;
	static LPDIRECT3DTEXTURE9 m_pTexture_Block[NUMTEXTURE];

	int m_movecnt_R, m_movecnt_L;
	bool m_movechange_R, m_movechange_L;	//移動方向を切り替える用
};
#endif






