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
