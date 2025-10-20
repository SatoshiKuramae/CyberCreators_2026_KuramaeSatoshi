//============================================================
//
//Cursor.h
//
//Author Kuramaesatoshi
//============================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "main.h"
#include "object2D.h"
#include "stageselect.h"

static const D3DXVECTOR3 CURSORPOS_STAGE1(140.0f, 295.0f, 0.0f);
static const D3DXVECTOR3 CURSORPOS_STAGE2(385.0f, 295.0f, 0.0f);
static const D3DXVECTOR3 CURSORPOS_STAGE3(650.0f, 295.0f, 0.0f);
static const D3DXVECTOR3 CURSORPOS_STAGE4(895.0f, 295.0f, 0.0f);
static const D3DXVECTOR3 CURSORPOS_STAGE5(1140.0f, 295.0f, 0.0f);

constexpr float CURSOR_ROT = 0.02f;
constexpr float CURSORSIZE_X = 200.0f;
constexpr float CURSORSIZE_Y = 200.0f;

//カーソルクラス
class CCursor : public CObject2D
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_3D;


	CCursor(int nPriority = 9);
	~CCursor();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CCursor* Create(D3DXVECTOR3 pos);
	static HRESULT Load();
	static void Unload();


private:
	static int m_pTexture;		//テクスチャ

	D3DXVECTOR3 m_DestPos;

};
#endif



