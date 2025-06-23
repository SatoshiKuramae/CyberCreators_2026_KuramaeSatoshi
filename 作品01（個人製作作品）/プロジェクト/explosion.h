//=======================================================
//
//explosion.h
//
//Author Kuramaesatoshi
//=======================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D.h"

#define MAX_EXPLOSION (500)		//爆発の最大数
#define EXPLOSION_TX_X (0.125f)
//爆発エフェクト構造体
class CExplosion : public CObject2D
{
public:
	//爆発構造体の定義
	typedef struct
	{
		int nCounterAnim;	//アニメーションカウンター
		int nPatternAnim;	//アニメーションパターンNo.
	}Explosion;

	CExplosion();
	~CExplosion();
	HRESULT Init();
	void Uninit();
	void Draw();
	void Update();
	static CExplosion* Create(D3DXVECTOR3 pos);
	static HRESULT Load();	//テクスチャのロード
	static void Unload();

private:
	static LPDIRECT3DTEXTURE9 m_pTextureExplosion;

};
#endif
