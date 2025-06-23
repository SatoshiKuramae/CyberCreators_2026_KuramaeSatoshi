//============================================================
//
//enemy.h
//
//============================================================
#ifndef _CENEMY_H_
#define _CENEMY_H_
#include "main.h"
#include "object2D.h"
#define TEX_X_Enemy (0.25f)
#define PLYAYER_SP (10.0f)
//2Dオブジェクトクラス
class CEnemy : public CObject2D
{
public:
	enum EnemySTATE
	{
		STATE_NOMAL_R,
		STATE_NOMAL_L,
		STATE_RUN_R,
		STATE_RUN_L
	};
	CEnemy(int nPriority = 4);
	~CEnemy() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	D3DXVECTOR3 Collision_Y(D3DXVECTOR3 pos);
	D3DXVECTOR3 Collision_X(D3DXVECTOR3 pos);
	void Enemymove();
	void EnemyShotAngle();
	static CEnemy* Create(D3DXVECTOR3 pos);
	static HRESULT Load();	//テクスチャのロード
	static void Unload();
private:
	static D3DXVECTOR3 m_PosOld;
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	int texcntEnemy;
};
#endif


