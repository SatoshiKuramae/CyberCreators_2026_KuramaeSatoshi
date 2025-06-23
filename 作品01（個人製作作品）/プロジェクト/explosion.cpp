//==============================================================
//
// explosion.h
//
//==============================================================
#include "explosion.h"
#include "manager.h"

//�ÓI�����o������
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion = nullptr;

//�R���X�g���N�^
CExplosion::CExplosion()
{
	
}
//�f�X�g���N�^
CExplosion::~CExplosion()
{

}

//������
HRESULT CExplosion::Init()
{

	CObject2D::Init();

	return S_OK;
}

//�I������
void CExplosion::Uninit()
{
	CObject2D::Uninit();
	////�e�N�X�`���̔j��
	//if (m_pTextureExplosion != nullptr)
	//{
	//	m_pTextureExplosion->Release();
	//	m_pTextureExplosion = nullptr;
	//}

	////���_�o�b�t�@�̔j��
	//if (m_pVtxBuffExplosion != nullptr)
	//{
	//	m_pVtxBuffExplosion->Release();
	//	m_pVtxBuffExplosion = nullptr;
	//}
}

//�X�V����
void CExplosion::Update()
{
	CObject2D::Update();
	//VERTEX_2D* pVtx;
	//m_Explosion->nCounterAnim++;
	//if (m_Explosion->nCounterAnim == 5)
	//{
	//	m_Explosion->nCounterAnim = 0;
	//	m_Explosion->nPatternAnim++;
	//	if (m_Explosion->nPatternAnim >= 8)
	//	{
	//		Release();
	//	}
	//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//	m_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	//	pVtx[0].tex.x += EXPLOSION_TX_X;
	//	pVtx[1].tex.x += EXPLOSION_TX_X;
	//	pVtx[2].tex.x += EXPLOSION_TX_X;
	//	pVtx[3].tex.x += EXPLOSION_TX_X;
	//	//���_�o�b�t�@���A�����b�N
	//	m_pVtxBuffExplosion->Unlock();
	//}
}

//�`�揈��
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//CExplosion����
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion();
	//�e�N�X�`���̐���
	pExplosion->BindTexture(m_pTextureExplosion, D3DXVECTOR2(8, 1));
	pExplosion->Setpos(pos);
	pExplosion->SetParam(300, 300);
	pExplosion->Init();
	
	

	return pExplosion;
}

//���[�h
HRESULT CExplosion::Load()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTextureExplosion == nullptr)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "texture\\explosion000.png", &m_pTextureExplosion);
	}
	return S_OK;
}

//�A�����[�h
void CExplosion::Unload()
{
	if (m_pTextureExplosion != nullptr)
	{
		m_pTextureExplosion->Release();
		m_pTextureExplosion = nullptr;
	}
}