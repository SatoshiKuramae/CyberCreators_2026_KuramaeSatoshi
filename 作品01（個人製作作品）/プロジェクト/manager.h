//============================================================
//
//manager.h
//Author Kuramaesatoshi
//============================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"d3dx9.h"
#include <Windows.h>
#include "renderer.h"
#include "input.h"
#include "enemy.h"
#include "scene.h"
#include "texture.h"
#include "fade.h"
#include "model.h"
#include "sound.h"
#include "GameProgress.h"
class CCamera;
class CLight;
class CGameprogress;

//レンダラークラス
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();


	//static多すぎ！！！
	static CRenderer* GetRenderer();
	static CInputKeyboard* GetKeyboard();
	static CInputGamepad* GetJoypad();
	static CLight* GetLight();
	static void SetMode(CScene::MODE mode);
	static CTexture* GetTexture();
	static CScene* GetScene();
	static CFade* GetFade();
	static CModel* GetModel();
	static CSound* GetSound();
	static CGameprogress* GetGameProgress();
private:
	static CRenderer* m_pRenderer;	//レンダラー
	static CInputKeyboard* m_pKeyboard;
	static CInputGamepad* m_pJoypad;
	static CLight* m_pLight;	//ライト情報
	static CScene* m_pScene;
	static CTexture* m_pTexture;
	static CFade* m_pFade;
	static CModel* m_pModel;
	static CSound* m_pSound;
	static CGameprogress* m_pGameState;

};

#endif
