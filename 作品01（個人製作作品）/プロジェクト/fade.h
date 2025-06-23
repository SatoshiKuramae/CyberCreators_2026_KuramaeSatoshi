//=======================================================
//
//fade.h
//
//=======================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "object2D.h"
#include "scene.h"
constexpr float FADECOLOR_A(1.0f);

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX
	}FADE;

	CFade(int nPriority = 0);
	~CFade();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFade(CScene::MODE modeNext);
	void GetState(FADE fade);
private:
	LPDIRECT3DTEXTURE9 m_pTextureFade;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;

	float m_FadeTimer;

	CScene::MODE m_modeNext;
	static FADE m_Fadestate;
	static int m_pTexFade;

};
#endif