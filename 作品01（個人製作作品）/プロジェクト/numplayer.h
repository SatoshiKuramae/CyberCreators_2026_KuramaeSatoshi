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

//�@TODO�@�v���C���[�̎c�@���擾���\������
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
	int m_nFrameTimer;				//�t���[���̃^�C�}�[
	int m_nTimer;					//�^�C�}�[
	static CNumber* m_pNumber[NUMPLAYER_DIGIT];
	int m_nNumPlayer;
	CGameprogress* m_pGameProgress = nullptr;
};
#endif

