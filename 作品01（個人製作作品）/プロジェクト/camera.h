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
//�J����
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();	//�J�����̐ݒ�
	void SetQuake(int quakeflame, float quakesize);
	D3DXVECTOR3& GetRot() { return m_rot; }
	void SetPlayerManager(CPlayerManager* pManager) { m_pPlayerManager = pManager; }
private:
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//�����
	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;			//�r���[�s��
	D3DXVECTOR3 m_TargetPosV;		//�ړI�̒����_
	D3DXVECTOR3 m_rot;	//����
	bool m_flattery;		//�J�����̒Ǐ]
	int m_QuakeFlame;
	float m_QuakeSize;
	D3DXVECTOR3 m_AveragePlayer_pos;
	CPlayerManager* m_pPlayerManager = nullptr;
};
#endif
