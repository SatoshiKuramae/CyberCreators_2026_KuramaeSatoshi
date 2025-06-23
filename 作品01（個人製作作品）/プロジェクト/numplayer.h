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
#define NUMPLAYER_DIGIT (1)

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

