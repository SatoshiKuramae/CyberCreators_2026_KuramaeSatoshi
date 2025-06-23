//============================================================
//
//game.h
//
//============================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "scene.h"
#include "time.h"
#include "sound.h"
#include "numplayer.h"
#include <vector>
#include "camera.h"
#include "playermanager.h"
#include "gauge.h"
#include "gaugeframe.h"
#include "bg.h"
constexpr float  BLOCKSIZE(160.0f);
constexpr float  STARTPOS(2100.0f);
constexpr int NUMBBLOCK(500);
#define STAGE_TITLE	"data\\txtfile\\titlestage.txt" //ファイル名
#define STAGE_TUTORIAL	"data\\txtfile\\tutorialstage.txt" //ファイル名
#define STAGE1	"data\\txtfile\\stage01.txt" //ファイル名
#define STAGE2  "data\\txtfile\\stage02.txt"
#define STAGE3  "data\\txtfile\\stage03.txt"
#define STAGE4  "data\\txtfile\\stage04.txt"
#define STAGE5  "data\\txtfile\\stage05.txt"

class CGame : public CScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void LoadStage();
	void GetPause(bool bPause);
private:
	CTime* m_pTime;
	CNumplayer* m_pNumplayer;
	CGauge* m_pGauge;
	CGaugeframe* m_pGaugeframe;
	CSound* m_pSound_Game;
	CCamera* m_pCamera;
	CPlayerManager* m_PlayerManager = nullptr;
	CBg* m_pBg = nullptr;
	bool m_bPouse;
};
#endif