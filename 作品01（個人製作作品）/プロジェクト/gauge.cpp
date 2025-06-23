
//===============================================================================
//
//�Q�[�W�t���[��
// 
//===============================================================================
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "gauge.h"


//�R���X�g���N�^
CGauge::CGauge(int nPriority) :CObject2D(nPriority)
{

}

//�f�X�g���N�^
CGauge::~CGauge()
{

}

//�������i���_�o�b�t�@�����j
HRESULT CGauge::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;

	m_pTextureGauge = pTex->Regist("data\\texture\\gauge.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTextureGauge), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	
	return S_OK;
}

//�I��(���_�o�b�t�@�j��)
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//�X�V����(���_�o�b�t�@�̍X�V)
void CGauge::Update()
{
	// �A�r���e�B�Q�[�W�̒l���擾�i��: 0�`100�j
	float gauge = CManager::GetGameProgress()->GetAbilityGauge();

	// �ő�l�Ŋ�����-1.0�`1.0�ɕϊ�
	float rate = static_cast<float>(gauge) / 100;
	float rateM11 = rate * 2.0f - 1.0f;
	
	// �Q�[�W�������X�V
	SetRate(rateM11);
	CObject2D::Update();
}

//�`��i�|���S���`��j
void CGauge::Draw()
{
	CObject2D::Draw();
}

//����
CGauge* CGauge::Create(D3DXVECTOR3 pos)
{
	CGauge* pCGauge = new CGauge;
	pCGauge->Setpos(pos);
	pCGauge->SetParam(420.0f, 100.0f);
	pCGauge->Init();
	pCGauge->SetAnim(0.0f, 1.0f);

	return pCGauge;
}


void CGauge::SetRate(float rate)
{
	// rate �� 0.0f �` 1.0f �̒l�ɂ���i��: �Q�[�W50% �� 0.5f�j

	if (rate < -1.0f) {
		rate = -1.0f;
	}
	else if (rate > 1.0f) {
		rate = 1.0f;
	}
	SetLengthPolygon(rate);
}