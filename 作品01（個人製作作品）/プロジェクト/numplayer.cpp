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

//�R���X�g���N�^
CNumplayer::CNumplayer()
{

	m_nFrameTimer = 0;
	m_nTimer = 0;
	for (int i = 0; i < NUMPLAYER_DIGIT; i++)
	{
		m_pNumber[i] = nullptr;
	}
}
//�f�X�g���N�^
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
	//�v���C���[�}�l�[�W���[���玩�@�����擾
	m_pGameProgress = CManager::GetGameProgress();
	m_nNumPlayer = m_pGameProgress->GetLife();
	SetNumplayer();
}

//���݂̎c�@��\��
void CNumplayer::SetNumplayer()
{
	//�v���C���[�̎c�@�����擾
	//�ύX������Ώ������s�����y�����鏈���s������
	int digit = 1;
	int nPosTexU[NUMPLAYER_DIGIT];	//�e���̐������i�[
	float fTimerMIN, fTimerMAX;

	for (int nCntTimer = 0; nCntTimer < NUMPLAYER_DIGIT; nCntTimer++)
	{//�����Ƃɕ���
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


