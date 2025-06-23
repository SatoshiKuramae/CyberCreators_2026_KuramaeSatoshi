//=======================================================
//
//
//time.cpp
//
//
//=======================================================
#include "time.h"
#include "object.h"
#include "scene.h"

CNumber* CTime::m_pNumber[NUMDIGIT] = {};
int CTime::m_nResultTime = 0;
//コンストラクタ
CTime::CTime()
{

	m_nFrameTimer = 0;
	m_nTimer = 0;
	for (int i = 0; i < NUMDIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}
//デストラクタ
CTime::~CTime()
{
	for (int i = 0; i < NUMDIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}

HRESULT CTime::Init()
{
	CScene* pScene = nullptr;

	if (pScene->GetScene() == CScene::MODE_GAME)
	{
		for (int i = 0; i < NUMDIGIT; i++)
		{
			if (m_pNumber[i] == nullptr)
			{
				m_pNumber[i] = CNumber::Create(D3DXVECTOR3(700.0f - (45 * i), 50.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f));
			}
		}
	}
	else if (pScene->GetScene() == CScene::MODE_SELECT)
	{
		for (int i = 0; i < NUMDIGIT; i++)
		{
			if (m_pNumber[i] == nullptr)
			{
				m_pNumber[i] = CNumber::Create(D3DXVECTOR3(1080.0f - (80.0f * i), 550.0f, 0.0f), D3DXVECTOR2(110.0f, 150.0f));
			}
		}
	}
	else if (pScene->GetScene() == CScene::MODE_RESULT_CLEAR)
	{
		for (int i = 0; i < NUMDIGIT; i++)
		{
			if (m_pNumber[i] == nullptr)
			{
				m_pNumber[i] = CNumber::Create(D3DXVECTOR3(750.0f - (90.0f * i), 580.0f, 0.0f), D3DXVECTOR2(120.0f, 170.0f));
			}
		}
	}
	return S_OK;
}

void CTime::Uninit()
{
	for (int i = 0; i < NUMDIGIT; i++)
	{
		if (m_pNumber[i] != nullptr)
		{
			m_pNumber[i]->Uninit();
		}
	}
}

void CTime::Update()
{
	m_nFrameTimer++;
	SetTimer();
}

void CTime::SetTimer()
{
	int digit = 1;
	int nPosTexU[NUMDIGIT];	//各桁の数字を格納
	float fTimerMIN, fTimerMAX;
	if (m_nFrameTimer >= 60)
	{
		m_nFrameTimer = 0;
		m_nTimer++;
	}
	for (int nCntTimer = 0; nCntTimer < NUMDIGIT; nCntTimer++)
	{//桁ごとに分解
		nPosTexU[nCntTimer] = m_nTimer / digit % 10;
		digit *= 10;
	}
	for (int i = 0; i < NUMDIGIT; i++)
	{
		fTimerMIN = nPosTexU[i] * 0.1f;
		fTimerMAX = fTimerMIN + 0.1f;
		m_pNumber[i]->Setnumber(fTimerMIN, fTimerMAX);
	}
	m_nResultTime = m_nTimer;
}

//リザルト画面の記録
void CTime::ResultTimer()
{
	int digit_Re = 1;
	int nPosTexU_Re[NUMDIGIT];	//各桁の数字を格納
	float fTimerMIN_Re, fTimerMAX_Re;
	
	CScene* pScene = nullptr;
	if (pScene->GetScene() == CScene::MODE_RESULT_CLEAR)
	{
		for (int nCntTimer = 0; nCntTimer < NUMDIGIT; nCntTimer++)
		{//桁ごとに分解
			nPosTexU_Re[nCntTimer] = m_nResultTime / digit_Re % 10;
			digit_Re *= 10;
		}
		for (int i = 0; i < NUMDIGIT; i++)
		{
			fTimerMIN_Re = nPosTexU_Re[i] * 0.1f;
			fTimerMAX_Re = fTimerMIN_Re + 0.1f;
			m_pNumber[i]->Setnumber(fTimerMIN_Re, fTimerMAX_Re);
		}
	}
}

//ステージごとの記録を出力
void CTime::RankTime(int nRankTime) {
	int digit_Ra = 1;
	int nPosTexU_Ra[NUMDIGIT];	//各桁の数字を格納
	float fTimerMIN_Ra, fTimerMAX_Ra;

	CScene* pScene = nullptr;
	//画面がステージ選択だったら
	if (pScene->GetScene() == CScene::MODE_SELECT)
	{
		for (int nCntTimer = 0; nCntTimer < NUMDIGIT; nCntTimer++)
		{//桁ごとに分解
			nPosTexU_Ra[nCntTimer] = nRankTime / digit_Ra % 10;
			digit_Ra *= 10;
		}
		for (int i = 0; i < NUMDIGIT; i++)
		{
			fTimerMIN_Ra = nPosTexU_Ra[i] * 0.1f;
			fTimerMAX_Ra = fTimerMIN_Ra + 0.1f;
			m_pNumber[i]->Setnumber(fTimerMIN_Ra, fTimerMAX_Ra);
		}
	}
}