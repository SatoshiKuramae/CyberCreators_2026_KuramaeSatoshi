//===============================================================================
//
// �I����ʂ̃J�[�\��
// 
//===============================================================================

#include "object3D.h"
#include "main.h"
#include "manager.h"
#include "background.h"
#include "texture.h"
#include "stageselect.h"
int CBackGraund::m_pTexture = 0;
//�R���X�g���N�^
CBackGraund::CBackGraund(int nPriority) :CObject2D(nPriority)
{
	m_DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
// �f�X�g���N�^
CBackGraund::~CBackGraund()
{

}

//������
HRESULT CBackGraund::Init()
{
	CTexture* pTex = CManager::GetTexture();

	m_pTexture = pTex->Regist("data\\texture\\cursor.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTexture), D3DXVECTOR2(1, 1));
	CObject2D::Init();
	return S_OK;
}

//�`�揈��
void CBackGraund::Draw()
{
	CObject2D::Draw();
}

//�X�V����
void CBackGraund::Update()
{
	if (CStageselect::GetStageSelect() == 1)
	{
		m_DestPos = (D3DXVECTOR3(140.0f, 295.0f,0.0f));
	}
	else if (CStageselect::GetStageSelect() == 2)
	{
		m_DestPos = (D3DXVECTOR3(385.0f, 295.0f, 0.0f));
	}
	else if (CStageselect::GetStageSelect() == 3)
	{
		m_DestPos = (D3DXVECTOR3(650.0f, 295.0f, 0.0f));
	}
	else if (CStageselect::GetStageSelect() == 4)
	{
		m_DestPos = (D3DXVECTOR3(895.0f, 295.0f, 0.0f));
	}
	else if (CStageselect::GetStageSelect() == 5)
	{
		m_DestPos = (D3DXVECTOR3(1140.0f, 295.0f, 0.0f));
	}
	
	m_posPolygon = m_DestPos;
	m_rotPolygon.z+=0.02f;

	CBackGraund::Setpos(m_posPolygon);

	CObject2D::Update();
}

//�I������
void CBackGraund::Uninit()
{
	CObject2D::Uninit();
	
}

//����
CBackGraund* CBackGraund::Create(D3DXVECTOR3 pos)
{
	CBackGraund* pBackGround = new CBackGraund;

	pBackGround->Setpos(pos);
	pBackGround->SetParam(200.0f, 200.0f);
	pBackGround->Init();
	pBackGround->SetAnim(0.0f, 1.0f);
	return pBackGround;
}


//���[�h
HRESULT CBackGraund::Load()
{
	return S_OK;
}

//�A�����[�h
void CBackGraund::Unload()
{
	
}
