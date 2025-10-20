//============================================================
//
//tutorial.h
//Author Kuramaesatoshi
//============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "playablesene.h"
#include "sound.h"
#include "camera.h"
#include "playermanager.h"
#include "gauge.h"
#include"gaugeframe.h"
#include "numplayer.h"
#include "tutorialUI.h"
#include "bg.h"

static const D3DXVECTOR3 TUTORIALUI_POS(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f);

//チュートリアルシーン
class CTutorial : public CPlayableScene
{
public:
	CTutorial();
	~CTutorial() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void TutorialLoad();

private:
	CSound* m_pSound_Tutorial;
	CCamera* m_pCamera;
	CGauge* m_pGauge;
	CGaugeframe* m_pGaugeframe;
	CNumplayer* m_pNumplayer = nullptr;
	CTutorialUI* m_pTutorialUI = nullptr;
	CBg* m_pBg = nullptr;
};
#endif
