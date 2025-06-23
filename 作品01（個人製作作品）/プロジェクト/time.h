//===============================================================================
//
//texture.cpp
// 
//===============================================================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "object.h"
#include "number.h"
#include <iostream>
#include <string>
#include "texture.h"
#define NUMDIGIT (3)

class CTime 
{
public:
	CTime();
	~CTime();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetTimer();
	void ResultTimer();
	void RankTime(int nRankTime);
	int GetTime() { return m_nResultTime; }
private:
	D3DXVECTOR3 m_Timerpos;
	int m_nFrameTimer;				//フレームのタイマー
	int m_nTimer;					//タイマー
	static CNumber* m_pNumber[NUMDIGIT];
	static int m_nResultTime;
};
#endif
