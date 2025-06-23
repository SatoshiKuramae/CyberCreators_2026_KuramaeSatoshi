//============================================================
//
//enemy.cpp
//
//============================================================
#include "Enemy.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = nullptr;
D3DXVECTOR3 CEnemy::m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//コンストラクタ
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	texcntEnemy = 0;
}

//デストラクタ
CEnemy::~CEnemy()
{

}

//初期化（頂点バッファ生成）
HRESULT CEnemy::Init()
{
	CObject::SetType(TYPE::ENEMY);
	CObject2D::Init();

	return S_OK;
}

//終了(頂点バッファ破棄)
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//更新処理(頂点バッファの更新)
void CEnemy::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	D3DXVECTOR3 pos;
	pos = GetPos();

	Enemymove();
	pos += m_move;
	EnemyShotAngle();
	pos = Collision_Y(pos);
	pos = Collision_X(pos);
	


	//移動量を更新（減速）
	m_move.x += (0.0f - m_move.x) * 1.0f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	Setpos(pos);
	CObject2D::Update();
}

//描画（ポリゴン描画）
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//プレイヤー移動
void CEnemy::Enemymove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetKeyboardPress(DIK_J) == true)
	{//Aキーが押された

		if (pKeyboard->GetKeyboardPress(DIK_W) == true)
		{//左上移動

			m_move.x = sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_K) == true)
		{//左下移動

			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{//左移動
			m_move.x = -PLAYER_SPEED;
		}

	}
	else if (pKeyboard->GetKeyboardPress(DIK_K) == true)
	{//Kキーが押された

		if (pKeyboard->GetKeyboardPress(DIK_J) == true)
		{//左下移動

			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_L) == true)
		{//右下移動


			m_move.x = sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{//下移動

			m_move.y = PLAYER_SPEED;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_L) == true)
	{//Dキーが押された


		if (pKeyboard->GetKeyboardPress(DIK_K) == true)
		{//右下移動

			//移動量を更新（増加）
			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_I) == true)
		{//右上移動


			//移動量を更新（増加）
			m_move.x = sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * -PLAYER_SPEED;
		}
		else
		{//右移動

			m_move.x = PLAYER_SPEED;
		}
	}
	//ジャンプ
	if (pKeyboard->GetKeyboardTrigger(DIK_O) == true)
	{
		
	}
}

//射撃方向操作
void CEnemy::EnemyShotAngle()
{
	
}

//Y座標の当たり判定
D3DXVECTOR3 CEnemy::Collision_Y(D3DXVECTOR3 pos)
{
	m_PosOld = pos;
	for (int i = 0; i < NUMBLOCK; i++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::GetObject(i, 4);

		if (pObj != nullptr)
		{
			CBlock* pBlock = (CBlock*)pObj;
			pBlock->GetPos();
			//種類の取得
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::BLOCK)
			{
				
			}
		}
	}

	return pos;
}

//X座標の当たり判定
D3DXVECTOR3 CEnemy::Collision_X(D3DXVECTOR3 pos)
{
	m_PosOld = pos;
	for (int i = 0; i < NUMBLOCK; i++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::GetObject(i, 4);

		if (pObj != nullptr)
		{
			CBlock* pBlock = (CBlock*)pObj;
			pBlock->GetPos();
			//種類の取得
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::BLOCK)
			{
				
			}
		}
	}

	return pos;
}
//Object2D生成
CEnemy* CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy* pObject2D = new CEnemy;
	pObject2D->Init();
	pObject2D->BindTexture(m_pTexture, D3DXVECTOR2(4, 1));
	pObject2D->Setpos(pos);
	pObject2D->SetParam(100.0f, 100.0f);
	return pObject2D;
}

HRESULT CEnemy::Load()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTexture == nullptr)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, "texture\\bluedevil.png", &m_pTexture);
	}
	return S_OK;
}

//アンロード
void CEnemy::Unload()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
