//============================================================
//
//scene.h
//Author Kuramaesatoshi
// 
//============================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include"main.h"
#include <Windows.h>
#include "playermanager.h"
#include "block.h"

//�V�[���N���X
class CScene
{
public:
	//��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_SELECT,
		MODE_GAME,
		MODE_RESULT_CLEAR,
		MODE_RESULT_GAMEOVER,
		MODE_MAX,
	}MODE;

	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);
	static MODE GetScene();


private:
	static MODE m_Mode;
};

#endif
