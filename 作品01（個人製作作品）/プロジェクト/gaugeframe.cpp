
//===============================================================================
//
//�Q�[�W�t���[��
// gaugeflame.cpp
// Author:Satoshi Kuramae
//===============================================================================
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "gaugeframe.h"


//�R���X�g���N�^
CGaugeframe::CGaugeframe(int nPriority) :CObject2D(nPriority)
{

}

//�f�X�g���N�^
CGaugeframe::~CGaugeframe()
{

}

//�������i���_�o�b�t�@�����j
HRESULT CGaugeframe::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;

	m_pTextureGaugeframe = pTex->Regist("data\\texture\\gaugeframe.png");


	CObject2D::BindTexture(pTex->GetAddress(m_pTextureGaugeframe), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	
	return S_OK;
}

//�I��(���_�o�b�t�@�j��)
void CGaugeframe::Uninit()
{
	CObject2D::Uninit();
}

//�X�V����(���_�o�b�t�@�̍X�V)
void CGaugeframe::Update()
{
	CObject2D::Update();
}

//�`��i�|���S���`��j
void CGaugeframe::Draw()
{
	CObject2D::Draw();
}

//����
CGaugeframe* CGaugeframe::Create(D3DXVECTOR3 pos)
{
	CGaugeframe* pCGaugeframe = new CGaugeframe;
	pCGaugeframe->Setpos(pos);
	pCGaugeframe->SetParam(480.0f, 150.0f);
	pCGaugeframe->Init();
	pCGaugeframe->SetAnim(0.0f, 1.0f);

	return pCGaugeframe;
}
