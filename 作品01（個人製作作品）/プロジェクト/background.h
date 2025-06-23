//============================================================
//
//floor.h
//
//============================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "main.h"
#include "object2D.h"
#include "stageselect.h"


//2Dオブジェクトクラス
class CBackGraund : public CObject2D
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_3D;


	CBackGraund(int nPriority = 9);
	~CBackGraund();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CBackGraund* Create(D3DXVECTOR3 pos);
	static HRESULT Load();
	static void Unload();


private:
	static int m_pTexture;		//テクスチャ

	D3DXVECTOR3 m_DestPos;

};
#endif



