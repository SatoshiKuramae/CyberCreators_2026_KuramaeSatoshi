//============================================================
//
//game.h
//Author Kuramaesatoshi
//============================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "scene.h"
#include "object2D.h"
#include "sound.h"
#include "time.h"
#include "bg.h"
#define NUM_STAGE (5)
#define STAGE01_TIME (68)
#define STAGE02_TIME (30)
#define STAGE03_TIME (45)
#define STAGE04_TIME (70)
#define STAGE05_TIME (40)
class CStageselect : public CScene
{
	typedef enum
	{
		STAGE_NONE,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGETITLE,
		STAGE_MAX,
	}SELECTSTAGE;

public:
	CStageselect();
	~CStageselect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static int GetStageSelect();
	static int GetBestTime();
private:
	static int m_NowSelect;		//‘I‘ð‰æ–Ê‚Å‰½”Ô–Ú‚ª‘I‘ð‚³‚ê‚Ä‚é‚©—p
	static int m_nBesttime;
	CSound* m_pSound_Select;
	CTime* m_pTime_Select;
	CBg* m_pBg = nullptr;
};
#endif
