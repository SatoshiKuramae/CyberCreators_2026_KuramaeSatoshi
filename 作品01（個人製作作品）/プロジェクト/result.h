//============================================================
//
//result.h
//Author Kuramaesatoshi
//============================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include "time.h"
#include "sound.h"
#include "resultrank.h"
#include "bg.h"

static const D3DXVECTOR3 CLEAR_RESULTUI_POS(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f);

static const D3DXVECTOR3 RESULTRANK_UI_POS(MAXPOS_X / 2, MAXPOS_Y / 2 - 70.0f, 0.0f);
class CResult : public CScene
{
public:
	CResult();
	~CResult() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CTime* m_pTime_Result;
	CNumber* m_pNumber[NUMDIGIT];
	CSound* m_pSound_Result;
	CBg* m_pBg = nullptr;
};

#endif
