//=======================
//
//フェード処理:fade.cpp
//Author Kuramaesatoshi
//
//=======================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "manager.h"
#include "texture.h"

CFade::FADE CFade::m_Fadestate = FADE_NONE;

//==============================
//初期化処理
//==============================
HRESULT CFade::Init()
{

	LPDIRECT3DDEVICE9 pDevice;


	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	m_Fadestate = FADE_NONE;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "", &m_pTextureFade);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();

	return S_OK;
}

//========================
//終了処理
//========================
void CFade::Uninit(void)
{
	
}

void CFade::Update(void)
{
	CScene::MODE mode = m_modeNext;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Fadestate != FADE_NONE)
	{
		if (m_Fadestate == FADE_IN)
		{//フェードイン状態
			m_FadeTimer += 0.08f;		//ポリゴンを透明にしていく

			if (m_FadeTimer > 1.0f)
			{
				CManager::SetMode(mode);
				m_FadeTimer = 1.0f;
				m_Fadestate = FADE_OUT;		//何もしていない状態にする
			}
		}
		else if (m_Fadestate == FADE_OUT)
		{//フェードアウト状態
			m_FadeTimer -= 0.05f;

			if (m_FadeTimer < 0.0f)
			{
				m_FadeTimer = 0.0f;
				m_Fadestate = FADE_NONE;
			}
		}
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);

	//頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();
}

//==============================
//描画処理
//==============================
void CFade::Draw(void)
{
	if (m_Fadestate == FADE_NONE)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


void CFade::SetFade(CScene::MODE modeNext)
{
	m_Fadestate = FADE_IN;
	m_modeNext = modeNext;
	
}


void CFade::GetState(FADE fade)
{
	m_Fadestate = fade;
}

CFade::CFade(int nPriority)
{
	m_FadeTimer = 0.0f;
}

CFade::~CFade()
{
	m_FadeTimer = 0.0f;
}