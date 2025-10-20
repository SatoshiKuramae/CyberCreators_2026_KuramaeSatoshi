//============================================================
//
//game.h
//Author Kuramaesatoshi
//============================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "scene.h"
#include "playablesene.h"
#include "time.h"
#include "sound.h"
#include "numplayer.h"
#include <vector>
#include "camera.h"
#include "playermanager.h"
#include "gauge.h"
#include "gaugeframe.h"
#include "bg.h"

static const D3DXVECTOR3 GAMEUI_POS(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f);
//ÉQÅ[ÉÄÉVÅ[Éì
class CGame : public CPlayableScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Load();
	void GetPause(bool bPause);

private:
	CTime* m_pTime;
	CNumplayer* m_pNumplayer;
	CGauge* m_pGauge;
	CGaugeframe* m_pGaugeframe;
	CSound* m_pSound_Game;
	CCamera* m_pCamera;
	CBg* m_pBg = nullptr;
	bool m_bPouse;

	const char* m_filePath;
};
#endif