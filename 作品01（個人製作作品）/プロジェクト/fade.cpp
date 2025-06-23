//=======================
//
//�t�F�[�h����:fade.cpp
//Author Kuramaesatoshi
//
//=======================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "manager.h"
#include "texture.h"

CFade::FADE CFade::m_Fadestate = FADE_NONE;

//==============================
//����������
//==============================
HRESULT CFade::Init()
{

	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	m_Fadestate = FADE_NONE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "", &m_pTextureFade);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();

	return S_OK;
}

//========================
//�I������
//========================
void CFade::Uninit(void)
{
	
}

void CFade::Update(void)
{
	CScene::MODE mode = m_modeNext;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Fadestate != FADE_NONE)
	{
		if (m_Fadestate == FADE_IN)
		{//�t�F�[�h�C�����
			m_FadeTimer += 0.08f;		//�|���S���𓧖��ɂ��Ă���

			if (m_FadeTimer > 1.0f)
			{
				CManager::SetMode(mode);
				m_FadeTimer = 1.0f;
				m_Fadestate = FADE_OUT;		//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (m_Fadestate == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_FadeTimer -= 0.05f;

			if (m_FadeTimer < 0.0f)
			{
				m_FadeTimer = 0.0f;
				m_Fadestate = FADE_NONE;
			}
		}
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeTimer);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();
}

//==============================
//�`�揈��
//==============================
void CFade::Draw(void)
{
	if (m_Fadestate == FADE_NONE)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


void CFade::SetFade(CScene::MODE modeNext)
{
	m_Fadestate = FADE_IN;
	m_modeNext = modeNext;
	
}


void CFade::GetState(FADE fade)
{
	m_Fadestate = fade;
}

CFade::CFade(int nPriority)
{
	m_FadeTimer = 0.0f;
}

CFade::~CFade()
{
	m_FadeTimer = 0.0f;
}