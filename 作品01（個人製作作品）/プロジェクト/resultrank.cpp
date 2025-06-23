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

//�R���X�g���N�^
CResultrank::CResultrank(int nPriority) :CObject2D(nPriority)
{
	
}

// �f�X�g���N�^
CResultrank::~CResultrank()
{

}

//������
HRESULT CResultrank::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CTime* pTime = nullptr;
	CStageselect* pStageselect = nullptr;

	m_Besttime = pStageselect->GetBestTime();		//�X�e�[�W���Ƃ̃x�X�g�^�C�����擾
	m_PlayerTime = pTime->GetTime();				//����̌��ʃ^�C�����擾

	//����̌��ʂ��x�X�g�^�C����葁�����
	if (m_PlayerTime < m_Besttime)
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_S.png");
	}
	//�x�X�g�^�C����荷��10�b�ȓ��̏ꍇ
	else if (m_PlayerTime < m_Besttime + RANK_DIFF)
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_A.png");
	}
	//�����P�O�b�ȏ�̏ꍇ
	else
	{
		m_nTextureResult = pTex->Regist("data\\texture\\resultrank_B.png");
	}
	CObject2D::BindTexture(pTex->GetAddress(m_nTextureResult), D3DXVECTOR2(1, 1));

	CObject2D::Init();
	return S_OK;
}

//�I������
void CResultrank::Uninit()
{
	CObject2D::Uninit();
}

//�`�揈��
void CResultrank::Draw()
{
	CObject2D::Draw();
}

//�X�V����
void CResultrank::Update()
{
	CObject2D::Update();
}

//����
CResultrank* CResultrank::Create(D3DXVECTOR3 pos)
{
	CResultrank* pNumber = new CResultrank;
	pNumber->Setpos(pos);
	pNumber->SetParam(RANKUI_PARAM, RANKUI_PARAM);
	pNumber->SetAnim(0.0f, 1.0f);
	pNumber->Init();
	
	return pNumber;
}
