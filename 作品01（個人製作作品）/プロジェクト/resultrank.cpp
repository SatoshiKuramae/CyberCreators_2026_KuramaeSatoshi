//===============================================================================
//
// resultrank.cpp
// 
//Author Kuramaesatoshi
//===============================================================================

#include "resultrank.h"
#include "manager.h"
#include "texture.h"
#include "object.h"
#include "stageselect.h"
#include "time.h"

int CResultrank::m_nTextureResult = 0;

//コンストラクタ
CResultrank::CResultrank(int nPriority) :CObject2D(nPriority)
{
	
}

// デストラクタ
CResultrank::~CResultrank()
{

}

//初期化
HRESULT CResultrank::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CTime* pTime = nullptr;
	CStageselect* pStageselect = nullptr;

	m_Besttime = pStageselect->GetBestTime();		//ステージごとのベストタイムを取得
	m_PlayerTime = pTime->GetTime();				//今回の結果タイムを取得

	//今回の結果がベストタイムより早ければ
	if (m_PlayerTime < m_Besttime)
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_S.png");
	}
	//ベストタイムより差が10秒以内の場合
	else if (m_PlayerTime < m_Besttime + RANK_DIFF)
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_A.png");
	}
	//差が１０秒以上の場合
	else
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_B.png");
	}
	CObject2D::BindTexture(pTex->GetAddress(m_nTextureResult), D3DXVECTOR2(1, 1));

	CObject2D::Init();
	return S_OK;
}

//終了処理
void CResultrank::Uninit()
{
	CObject2D::Uninit();
}

//描画処理
void CResultrank::Draw()
{
	CObject2D::Draw();
}

//更新処理
void CResultrank::Update()
{
	CObject2D::Update();
}

//生成
CResultrank* CResultrank::Create(D3DXVECTOR3 pos)
{
	CResultrank* pNumber = new CResultrank;
	pNumber->Setpos(pos);
	pNumber->SetParam(RANKUI_PARAM, RANKUI_PARAM);
	pNumber->SetAnim(0.0f, 1.0f);
	pNumber->Init();
	
	return pNumber;
}
