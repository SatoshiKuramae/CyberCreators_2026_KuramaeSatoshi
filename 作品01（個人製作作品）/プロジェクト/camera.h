//===============================================================================
//
//camera.cpp
// 
//===============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "playermanager.h"
constexpr float  CAMERASPEED(1.0f);
//カメラ
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();	//カメラの設定
	void SetQuake(int quakeflame, float quakesize);
	D3DXVECTOR3& GetRot() { return m_rot; }
	void SetPlayerManager(CPlayerManager* pManager) { m_pPlayerManager = pManager; }
private:
	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_vecU;				//上方向
	D3DXMATRIX m_mtxProjection;		//プロジェクション行列
	D3DXMATRIX m_mtxView;			//ビュー行列
	D3DXVECTOR3 m_TargetPosV;		//目的の注視点
	D3DXVECTOR3 m_rot;	//向き
	bool m_flattery;		//カメラの追従
	int m_QuakeFlame;
	float m_QuakeSize;
	D3DXVECTOR3 m_AveragePlayer_pos;
	CPlayerManager* m_pPlayerManager = nullptr;
};
#endif
