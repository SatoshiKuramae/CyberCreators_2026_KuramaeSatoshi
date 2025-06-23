//============================================================
//
//title.h
//
//============================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "scene.h"
#include "sound.h"
#include "camera.h"
#include "playermanager.h"
#include "bg.h"
class CTitle : public CScene
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
	CPlayerManager* m_PlayerManager = nullptr;
	CCamera* m_pCamera;
	CBg* m_pBg = nullptr;
};
#endif
