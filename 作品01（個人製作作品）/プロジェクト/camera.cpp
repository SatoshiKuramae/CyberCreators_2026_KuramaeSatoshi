//===============================================================================
//
// camera.cpp
// 
//===============================================================================
#include "camera.h"
#include "manager.h"
#include"input.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>


constexpr float  CAMERALENGTH_Y(2500.0f);
constexpr float  CAMERALENGTH_Z(2500.0f);
//コンストラクタ
CCamera::CCamera()
{
	m_QuakeFlame = 0;
	m_QuakeSize = 0;
}
//デストラクタ
CCamera::~CCamera()
{

}

//初期設定
HRESULT CCamera::Init()
{
	m_TargetPosV.y = CAMERAPOS_V_Y;
	m_TargetPosV.z = CAMERAPOS_V_Z;
	m_flattery = true;
	CCamera::m_posV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	CCamera::m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CCamera::m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	CCamera::m_rot = D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	m_AveragePlayer_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//カメラの設定
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), 
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	srand((unsigned int)clock()); // 現在時刻の情報で初期化

	D3DXVECTOR3 adjust = D3DXVECTOR3(0, 0, 0);
	if (m_QuakeFlame > 0)
	{
		m_QuakeFlame--;
		adjust.x = rand() % 100 + 1;
		adjust.y = rand() % 100 + 1;
		adjust.z = rand() % 100 + 1;
	}

	D3DXVECTOR3 CameraposV = m_posV + adjust;
	D3DXVECTOR3 CameraposR = m_posR + adjust;
	D3DXMatrixLookAtLH(&m_mtxView, &CameraposV, &CameraposR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//更新処理
void CCamera::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CScene* pScene = nullptr;

	//posR=注視点posV=視点vecU=視点のベクトル
	//視点の移動
	if (pKeyboard->GetKeyboardPress(DIK_X) == true)
	{
		m_rot.y += 0.1f;

		m_posV.x = sinf(m_rot.y + D3DX_PI) * sqrtf(m_TargetPosV.z * m_TargetPosV.z + m_TargetPosV.y * m_TargetPosV.y) / 2 + CCamera::m_posR.x;
		m_posV.z = cosf(m_rot.y + D3DX_PI) * sqrtf(m_TargetPosV.z * m_TargetPosV.z + m_TargetPosV.y * m_TargetPosV.y) / 2 + CCamera::m_posR.x;
	}
	if (pKeyboard->GetKeyboardPress(DIK_Z) == true)
	{
		m_rot.y -= 0.1f;

		m_posV.x = sinf(m_rot.y + D3DX_PI) * sqrtf(m_TargetPosV.z * m_TargetPosV.z + m_TargetPosV.y * m_TargetPosV.y) / 2 + CCamera::m_posR.x;
		m_posV.z = cosf(m_rot.y + D3DX_PI) * sqrtf(m_TargetPosV.z * m_TargetPosV.z + m_TargetPosV.y * m_TargetPosV.y) / 2 + CCamera::m_posR.x;
	}
	if (pKeyboard->GetKeyboardPress(DIK_Y) == true)
	{
		m_rot.x += 2.0f;
		m_posV.y += 2.0f;
	}
	if (pKeyboard->GetKeyboardPress(DIK_N) == true)
	{
		m_rot.x -= 2.0f;
		m_posV.y -= 2.0f;
	}

	//回転の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//注視点までの距離を変える
	if (pKeyboard->GetKeyboardPress(DIK_Q) == true)
	{
		m_posV.z += 1.0f;
		m_TargetPosV.z += 1.0f;
		m_TargetPosV.y -= 1.0f;
		m_TargetPosV.x -= 1.0f;
	}

	if (pKeyboard->GetKeyboardPress(DIK_E) == true)
	{
		m_posV.z -= 1.0f;
		m_TargetPosV.z += 1.0f;
		m_TargetPosV.y += 1.0f;
		m_TargetPosV.x += 1.0f;
	}

	//視点の位置移動（前後左右）
	if (pKeyboard->GetKeyboardPress(DIK_UP) == true)
	{
		m_posV.y += CAMERASPEED;
		m_posR.y += CAMERASPEED;
	}

	if (pKeyboard->GetKeyboardPress(DIK_DOWN) == true)
	{
		m_posV.z -= CAMERASPEED;
		m_posR.z -= CAMERASPEED;
	}

	if (pKeyboard->GetKeyboardPress(DIK_RIGHT) == true)
	{
		m_posV.x += CAMERASPEED;
		m_posR.x += CAMERASPEED;
	}
	if (pKeyboard->GetKeyboardPress(DIK_LEFT) == true)
	{
		m_posV.x -= CAMERASPEED;
		m_posR.x -= CAMERASPEED;
	}



	


	
	m_AveragePlayer_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	static D3DXVECTOR3 pos1, pos2;

	
	
	
		for (int i = 0; i < NUMOBJECT; i++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::GetObject(i, 3);
			if (pObj != nullptr)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;
				pPlayer->GetPos();

				m_posR.y = pPlayer->GetPos().y + 500.0f;
				//種類の取得
				CObject::TYPE type = pObj->GetType();

				if (type == CObject::TYPE::PLAYER01)
				{
					pos1 = pPlayer->GetPos();
				}
				else if (type == CObject::TYPE::PLAYER02)
				{
					pos2 = pPlayer->GetPos();
				}
			}
		}
		if (pScene->GetScene() == CScene::MODE_TITLE)
		{
			m_AveragePlayer_pos = pos1 + pos2;
			m_AveragePlayer_pos /= 2;
			m_posR.x = m_AveragePlayer_pos.x;
			m_posR.y = m_AveragePlayer_pos.y;
			m_posV.x = sinf(m_rot.y + D3DX_PI) * sqrtf(1000.0f * 1000.0f + 1000.0f * 1000.0f) / 2 +m_AveragePlayer_pos.x;
			m_posV.z = cosf(m_rot.y + D3DX_PI) * sqrtf(1000.0f * 1000.0f + 1000.0f * 1000.0f) / 2 +m_AveragePlayer_pos.z;
			m_posV.y = m_AveragePlayer_pos.y + 200.0f;
		}
		else
		{
			m_AveragePlayer_pos = pos1 + pos2;
			m_AveragePlayer_pos /= 2;
			m_posR.x = m_AveragePlayer_pos.x;
			m_posR.y = m_AveragePlayer_pos.y;
			m_posV.x = sinf(m_rot.y + D3DX_PI) * sqrtf(CAMERALENGTH_Y * CAMERALENGTH_Y + CAMERALENGTH_Z * CAMERALENGTH_Z) / 2 +m_AveragePlayer_pos.x;
			m_posV.z = cosf(m_rot.y + D3DX_PI) * sqrtf(CAMERALENGTH_Y * CAMERALENGTH_Y + CAMERALENGTH_Z * CAMERALENGTH_Z) / 2 +m_AveragePlayer_pos.z;
			m_posV.y = m_AveragePlayer_pos.y + 200.0f;
		}
		
	
	
}

void CCamera::SetQuake(int quakeflame, float quakesize)
{
	m_QuakeFlame = quakeflame;
	m_QuakeSize = quakesize;
}