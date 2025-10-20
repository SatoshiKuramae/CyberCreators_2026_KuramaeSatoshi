//===============================================================================
//
// �I����ʂ̃J�[�\��
// Background.cpp
// 
// Author:Satoshi Kuramae
//===============================================================================

#include "object3D.h"
#include "main.h"
#include "manager.h"
#include "background.h"
#include "texture.h"
#include "stageselect.h"
int CCursor::m_pTexture = 0;

//�R���X�g���N�^
CCursor::CCursor(int nPriority) :CObject2D(nPriority)
{
	m_DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
// �f�X�g���N�^
CCursor::~CCursor()
{

}

//������
HRESULT CCursor::Init()
{
	CTexture* pTex = CManager::GetTexture();

	m_pTexture = pTex->Regist("data\\texture\\cursor.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTexture), D3DXVECTOR2(1, 1));
	CObject2D::Init();
	return S_OK;
}

//�`�揈��
void CCursor::Draw()
{
	CObject2D::Draw();
}

//�X�V����
void CCursor::Update()
{
	if (CStageselect::GetStageSelect() == 1)
	{
		m_DestPos = CURSORPOS_STAGE1;
	}
	else if (CStageselect::GetStageSelect() == 2)
	{
		m_DestPos = CURSORPOS_STAGE2;
	}
	else if (CStageselect::GetStageSelect() == 3)
	{
		m_DestPos = CURSORPOS_STAGE3;
	}
	else if (CStageselect::GetStageSelect() == 4)
	{
		m_DestPos = CURSORPOS_STAGE4;
	}
	else if (CStageselect::GetStageSelect() == 5)
	{
		m_DestPos = CURSORPOS_STAGE5;
	}
	
	m_pos = m_DestPos;
	m_rotPolygon.z+= CURSOR_ROT;

	CCursor::Setpos(m_pos);

	CObject2D::Update();
}

//�I������
void CCursor::Uninit()
{
	CObject2D::Uninit();
	
}

//����
CCursor* CCursor::Create(D3DXVECTOR3 pos)
{
	CCursor* pBackGround = new CCursor;

	pBackGround->Setpos(pos);
	pBackGround->SetParam(CURSORSIZE_X, CURSORSIZE_Y);
	pBackGround->Init();
	pBackGround->SetAnim(0.0f, 1.0f);
	return pBackGround;
}


//���[�h
HRESULT CCursor::Load()
{
	return S_OK;
}

//�A�����[�h
void CCursor::Unload()
{
	
}
