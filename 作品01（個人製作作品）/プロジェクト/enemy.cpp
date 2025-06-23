//============================================================
//
//enemy.cpp
//
//============================================================
#include "Enemy.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = nullptr;
D3DXVECTOR3 CEnemy::m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//�R���X�g���N�^
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	texcntEnemy = 0;
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}

//�������i���_�o�b�t�@�����j
HRESULT CEnemy::Init()
{
	CObject::SetType(TYPE::ENEMY);
	CObject2D::Init();

	return S_OK;
}

//�I��(���_�o�b�t�@�j��)
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//�X�V����(���_�o�b�t�@�̍X�V)
void CEnemy::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	D3DXVECTOR3 pos;
	pos = GetPos();

	Enemymove();
	pos += m_move;
	EnemyShotAngle();
	pos = Collision_Y(pos);
	pos = Collision_X(pos);
	


	//�ړ��ʂ��X�V�i�����j
	m_move.x += (0.0f - m_move.x) * 1.0f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	Setpos(pos);
	CObject2D::Update();
}

//�`��i�|���S���`��j
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//�v���C���[�ړ�
void CEnemy::Enemymove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetKeyboardPress(DIK_J) == true)
	{//A�L�[�������ꂽ

		if (pKeyboard->GetKeyboardPress(DIK_W) == true)
		{//����ړ�

			m_move.x = sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_K) == true)
		{//�����ړ�

			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{//���ړ�
			m_move.x = -PLAYER_SPEED;
		}

	}
	else if (pKeyboard->GetKeyboardPress(DIK_K) == true)
	{//K�L�[�������ꂽ

		if (pKeyboard->GetKeyboardPress(DIK_J) == true)
		{//�����ړ�

			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_L) == true)
		{//�E���ړ�


			m_move.x = sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{//���ړ�

			m_move.y = PLAYER_SPEED;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_L) == true)
	{//D�L�[�������ꂽ


		if (pKeyboard->GetKeyboardPress(DIK_K) == true)
		{//�E���ړ�

			//�ړ��ʂ��X�V�i�����j
			m_move.x = sinf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
			m_move.y = cosf(-D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_I) == true)
		{//�E��ړ�


			//�ړ��ʂ��X�V�i�����j
			m_move.x = sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * -PLAYER_SPEED;
		}
		else
		{//�E�ړ�

			m_move.x = PLAYER_SPEED;
		}
	}
	//�W�����v
	if (pKeyboard->GetKeyboardTrigger(DIK_O) == true)
	{
		
	}
}

//�ˌ���������
void CEnemy::EnemyShotAngle()
{
	
}

//Y���W�̓����蔻��
D3DXVECTOR3 CEnemy::Collision_Y(D3DXVECTOR3 pos)
{
	m_PosOld = pos;
	for (int i = 0; i < NUMBLOCK; i++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::GetObject(i, 4);

		if (pObj != nullptr)
		{
			CBlock* pBlock = (CBlock*)pObj;
			pBlock->GetPos();
			//��ނ̎擾
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::BLOCK)
			{
				
			}
		}
	}

	return pos;
}

//X���W�̓����蔻��
D3DXVECTOR3 CEnemy::Collision_X(D3DXVECTOR3 pos)
{
	m_PosOld = pos;
	for (int i = 0; i < NUMBLOCK; i++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::GetObject(i, 4);

		if (pObj != nullptr)
		{
			CBlock* pBlock = (CBlock*)pObj;
			pBlock->GetPos();
			//��ނ̎擾
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::BLOCK)
			{
				
			}
		}
	}

	return pos;
}
//Object2D����
CEnemy* CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy* pObject2D = new CEnemy;
	pObject2D->Init();
	pObject2D->BindTexture(m_pTexture, D3DXVECTOR2(4, 1));
	pObject2D->Setpos(pos);
	pObject2D->SetParam(100.0f, 100.0f);
	return pObject2D;
}

HRESULT CEnemy::Load()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTexture == nullptr)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "texture\\bluedevil.png", &m_pTexture);
	}
	return S_OK;
}

//�A�����[�h
void CEnemy::Unload()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
