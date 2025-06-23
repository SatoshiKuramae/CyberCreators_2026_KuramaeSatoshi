//===============================================================================
//
//tutorialUI.cpp
//Author Kuramaesatoshi
//===============================================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_
#include "main.h"
#include "object.h"
#include "object2D.h"
#include <iostream>
#include <string>
#include "sound.h"
constexpr int NUM_TEX(5);
//テクスチャ管理
class CTutorialUI : public CObject2D
{
public:

	CTutorialUI(int nPriority = 15);
	~CTutorialUI() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CTutorialUI* Create(D3DXVECTOR3 pos);

private: 
	bool m_bCreateTutorial;		//クリエイトされた時のフラグ用
	int m_pTextureTutorial[NUM_TEX];
	int m_tutorialcnt;
	CSound* m_pSound_TutorialUI=nullptr;
};
#endif
