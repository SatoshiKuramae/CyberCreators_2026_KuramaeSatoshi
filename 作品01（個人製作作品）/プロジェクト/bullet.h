//=======================================================
//
//bullet.h
//
//=======================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "object2D.h"
#define MAX_BULLET (100)
#define BULLETSPEED (20.0f)
class CBullet :public CObject2D
{
public:
	CBullet(int nPriority = 2);
	~CBullet();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void Setpos(D3DXVECTOR3 pos);
	//bool CollisionEnemy(D3DXVECTOR3 pos);
	//bool CollisionPlayer(D3DXVECTOR3 pos);
	static HRESULT Load();	//テクスチャのロード
	static void Unload();
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
private:
	
	static LPDIRECT3DTEXTURE9 m_pTexturebullet;				//テクスチャ
	int m_Bulletlife;

};
#endif