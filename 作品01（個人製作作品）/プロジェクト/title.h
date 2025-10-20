//============================================================
//
//title.h
//Author Kuramaesatoshi
//============================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "playablesene.h"
#include "sound.h"
#include "camera.h"
#include "playermanager.h"
#include "bg.h"

static const D3DXVECTOR3 TITLEUI_POS(620.0f, 350.0f, 0.0f);

//タイトルシーン
class CTitle : public CPlayableScene
{
public:
	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void TitleLoad();
	CCamera* GetCamera() const { return m_pCamera; }
private:
	bool m_TutorialCreate;
	CSound* m_pSound_Title;
	CCamera* m_pCamera;
	CBg* m_pBg = nullptr;
};
#endif
