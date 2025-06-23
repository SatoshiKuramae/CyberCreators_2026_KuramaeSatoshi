//=======================================================
//
//
//time.cpp
//
//
//=======================================================
#include "numplayer.h"
#include "object.h"
#include "scene.h"
#include "manager.h"
CNumber* CNumplayer::m_pNumber[NUMPLAYER_DIGIT] = {};

//コンストラクタ
CNumplayer::CNumplayer()
{

	m_nFrameTimer = 0;
	m_nTimer = 0;
	for (int i = 0; i < NUMPLAYER_DIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}
//デストラクタ
CNumplayer::~CNumplayer()
{
	for (int i = 0; i < NUMPLAYER_DIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}

HRESULT CNumplayer::Init()
{
	m_nNumPlayer = 0;
	CScene* pScene = nullptr;

	if (pScene->GetScene() == CScene::MODE_GAME|| pScene->GetScene() == CScene::MODE_TUTORIAL)
	{
		for (int i = 0; i < NUMPLAYER_DIGIT; i++)
		{
			if (m_pNumber[i] == nullptr)
			{
				m_pNumber[i] = CNumber::Create(D3DXVECTOR3(310.0f - (45 * i), 650.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f));
			}
		}
	}
	
	return S_OK;
}

void CNumplayer::Uninit()
{
	for (int i = 0; i < NUMPLAYER_DIGIT; i++)
	{
		if (m_pNumber[i] != nullptr)
		{
			m_pNumber[i]->Uninit();
		}
	}
}

void CNumplayer::Update()
{
	//プレイヤーマネージャーから自機数を取得
	m_pGameProgress = CManager::GetGameProgress();
	m_nNumPlayer = m_pGameProgress->GetLife();
	SetNumplayer();
}

//現在の残機を表示
void CNumplayer::SetNumplayer()
{
	//プレイヤーの残機をを取得
	//変更があれば処理を行う等軽くする処理行うかも
	int digit = 1;
	int nPosTexU[NUMPLAYER_DIGIT];	//各桁の数字を格納
	float fTimerMIN, fTimerMAX;

	for (int nCntTimer = 0; nCntTimer < NUMPLAYER_DIGIT; nCntTimer++)
	{//桁ごとに分解
		nPosTexU[nCntTimer] = m_nNumPlayer / digit % 10;
		digit *= 10;
	}
	for (int i = 0; i < NUMPLAYER_DIGIT; i++)
	{
		fTimerMIN = nPosTexU[i] * 0.1f;
		fTimerMAX = fTimerMIN + 0.1f;
		m_pNumber[i]->Setnumber(fTimerMIN, fTimerMAX);
	}
	

}


