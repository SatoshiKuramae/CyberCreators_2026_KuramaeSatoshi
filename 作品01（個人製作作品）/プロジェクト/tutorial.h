//============================================================
//
//tutorial.h
//Author Kuramaesatoshi
//============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "scene.h"
#include "sound.h"
#include "camera.h"
#include "playermanager.h"
#include "gauge.h"
#include"gaugeframe.h"
#include "numplayer.h"
#include "tutorialUI.h"
#include "bg.h"
class CTutorial : public CScene
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
	CPlayerManager* m_PlayerManager = nullptr;
	CNumplayer* m_pNumplayer = nullptr;
	CTutorialUI* m_pTutorialUI = nullptr;
	CBg* m_pBg = nullptr;
};
#endif
