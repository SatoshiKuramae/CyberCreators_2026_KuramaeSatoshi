//===============================================================================
//
//numplayer.cpp
//Author Kuramaesatoshi
//===============================================================================
#ifndef _NUMPLAYER_H_
#define _NUMPLAYER_H_
#include "main.h"
#include "object.h"
#include "number.h"
#include "GameProgress.h"
#include <iostream>
#include <string>
#include "texture.h"
constexpr int NUMPLAYER_DIGIT(1);
constexpr float NUMPLAYER_UI_POS_X = (310.0f);
constexpr float NUMPLAYER_UI_POS_Y = (650.0f);
constexpr float NUMPLAYER_UI_SIZE_X = (50.0f);
constexpr float NUMPLAYER_UI_SIZE_Y = (100.0f);
constexpr float NUMPLAYER_UI_DIGITSIZE = (45.0f);
//　TODO　プレイヤーの残機を取得し表示する
class CNumplayer
{
public:
	CNumplayer();
	~CNumplayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetNumplayer();
	int GetTime() { return m_nNumPlayer; }
private:
	D3DXVECTOR3 m_Numberpos;
	int m_nFrameTimer;				//フレームのタイマー
	int m_nTimer;					//タイマー
	static CNumber* m_pNumber[NUMPLAYER_DIGIT];
	int m_nNumPlayer;
	CGameprogress* m_pGameProgress = nullptr;
};
#endif

