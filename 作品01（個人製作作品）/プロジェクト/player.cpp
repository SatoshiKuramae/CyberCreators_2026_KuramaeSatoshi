//===============================================================================
//
//player.cpp
// 
//Author Kuramaesatoshi
//===============================================================================

#include "objectX.h"
#include "manager.h"
#include "player.h"
#include "block.h"
#include "block.h"
#include "camera.h"
#include "floor.h"
#include "model.h"
#include "effect_x.h"

//�ÓI�����o������
D3DXVECTOR3 CPlayer::m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
LPD3DXMESH CPlayer::m_pMesh_Player[PLAYER_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat_Player[PLAYER_MAX] = {};
DWORD CPlayer::m_dwNumMat_Player[PLAYER_MAX] = {};
D3DXMATERIAL* CPlayer::m_pMaterial_Player = nullptr;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture_Player[NUM_TEXTURE] = {};
CItem* m_pItem = nullptr;
CSound* m_pSound_Player = nullptr;

int CPlayer::m_Numplayer = 0;
//�R���X�g���N�^
CPlayer::CPlayer()
{
	CPlayer::m_ControlPlayer = CPlayer::ControlPlayer::C_Player_1;
	m_PlayerState = ALIVE;
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init()
{
	/*CObject::SetType(TYPE::PLAYER);*/

	m_PlayerState_Block = STATE_NOMALBLOCK;

	m_bDeath = false;
	m_Goalflag = false;
	m_Itemflag = false;
	m_Jump = false;
	m_IsAbilityActive = false;
	m_PowerupCnt = 0;
	m_MagCnt = 0;
	m_Numplayer = 0;
	m_jumpPower = JUMP_INC;
	CPlayer::Load();
	CObjectX::Init();
	m_pSound_Player = CManager::GetSound();

	return S_OK;
}

//�I������
void CPlayer::Uninit()
{
	Unload();
	CObjectX::Uninit();
}

//�X�V����
void CPlayer::Update()
{
	if (m_Itemflag == true)
	{
		m_PowerupCnt ++;
		if (m_PowerupCnt <= POWERCOUNT)
		{
			CEffect_X::Create(m_pos, m_rot, "data\\xfile\\Player_Effect.x");
			
		}
		else
		{
			m_PowerupCnt = 0;
			m_Itemflag = false;
		}
		
		if (m_PowerupCnt == WARNINGLINE)
		{
			m_pSound_Player->PlaySound(CSound::SOUND_LABEL_WARNING);
		}
		
	}

	if (m_Goalflag == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_RESULT_CLEAR);
		m_Goalflag = false;
	}

	D3DXVECTOR3 pos;
	pos = GetPos();

	m_PosOld = pos;

	if (m_bEnableGravity) {
		m_move.y -= JUMP_DEC;  // �d�͉��Z
	}

	//�ړ��ʂ��X�V�i�����j
	m_move.x += (-m_move.x) * MOVEDEC;
	m_move.z += (-m_move.z) * MOVEDEC;

	pos += m_move;
	pos = Collision(pos);
	
	Setpos(pos);
}

//�v���C���[�ړ�
void CPlayer::Playermove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();
	auto stick = pJoypad->GetStick();

	// ���X�e�B�b�N���|����Ă������
	D3DXVECTOR3 JoyVector = { (float)CManager::GetJoypad()->GetJoyLX(),0.0f ,
		(float)CManager::GetJoypad()->GetJoyLY() };

	const float DEADZONE = DEAD_ZONE;
	
	//�p�b�h����
	if (fabsf(JoyVector.x) > DEADZONE || fabsf(JoyVector.z) > DEADZONE)
	{
		D3DXVec3Normalize(&JoyVector, &JoyVector);

		if (JoyVector.x < -STICK_ZONE)
		{
			m_move.x = -PLAYER_SPEED;
		}
		else if (JoyVector.x > STICK_ZONE)
		{
			m_move.x = PLAYER_SPEED;
		}
	}
	if (pKeyboard->GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		m_move.x = -PLAYER_SPEED;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		m_move.x = PLAYER_SPEED;
	}
	//�W�����v
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) == true || pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_B) == true)
	{
		UpdateJump();
	}
}

//�W�����v��p����
void CPlayer::UpdateJump() {
	if (m_Jump == true) {
		m_Jump = false;

		m_pSound_Player->PlaySound(CSound::SOUND_LABEL_JUMP);
		m_move.y += m_jumpPower;  // �� ���������Ő���
	}
}

//�`�揈��
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//�����蔻��i��,y���W�j
D3DXVECTOR3 CPlayer::Collision(D3DXVECTOR3 pos)
{
	for (int i = 0; i < NUMOBJECT; i++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::GetObject(i, 3);

		if (pObj != nullptr)
		{
			//��ނ̎擾
			CObject::TYPE type = pObj->GetType();

			//==========================================================
			//�u���b�N�Ƃ̔���
			//==========================================================
			if (type == CObject::TYPE::BLOCK)
			{
				CBlock* p3DBlock = (CBlock*)pObj;
				p3DBlock->GetPos();
				p3DBlock->GetBlockType();
				//�u���b�N�̏�ʂƓ���������
				if (pos.y - PLAYERCOLL <= p3DBlock->GetPos().y + BLOCK_Y
					&& m_PosOld.y - PLAYERCOLL > p3DBlock->GetPos().y + BLOCK_Y
					&& pos.x + PLAYERCOLL >= p3DBlock->GetPos().x - BLOCK_X
					&& pos.x - PLAYERCOLL <= p3DBlock->GetPos().x + BLOCK_X
					&& pos.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_Y
					&& pos.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y)
				{
					
					m_Jump = true;

					if (p3DBlock->GetBlockType() == CBlock::TYPE_NOMALBLOCK)
					{
						m_PlayerState_Block = STATE_NOMALBLOCK;
						m_move.y = 0.0f;
						pos.y = p3DBlock->GetPos().y + RESETPOS;
					}
					else if (p3DBlock->GetBlockType() == CBlock::TYPE_MOVE_BLOCK_R)
					{
						m_PlayerState_Block = STATE_MOVEBLOCK_R;
						m_move.y = 0.0f;
						pos.y = p3DBlock->GetPos().y + RESETPOS;
						pos.x += p3DBlock->GetMove().x;
					}
					else if (p3DBlock->GetBlockType() == CBlock::TYPE_MOVE_BLOCK_L)
					{
						m_PlayerState_Block = STATE_MOVEBLOCK_L;
						m_move.y = 0.0f;
						pos.y = p3DBlock->GetPos().y + RESETPOS;
						pos.x += p3DBlock->GetMove().x;
					}
					//N�Ƀu���b�N�ɐG������
					else if (p3DBlock->GetBlockType() == CBlock::TYPE_N_BLOCK)
					{
						m_PlayerState_Block = STATE_N_BLOCK;
						m_move.y = 0.0f;
						pos.y = p3DBlock->GetPos().y + RESETPOS;
					}
					else if (p3DBlock->GetBlockType() == CBlock::TYPE_S_BLOCK)
					{
						m_PlayerState_Block = STATE_S_BLOCK;
						m_move.y = 0.0f;
						pos.y = p3DBlock->GetPos().y + RESETPOS;
					}
					
				}

				//�u���b�N�̉��ʂɓ���������
				if (pos.y + PLAYERCOLL >= p3DBlock->GetPos().y - BLOCK_Y
					&& m_PosOld.y + PLAYERCOLL < p3DBlock->GetPos().y - BLOCK_X
					&& pos.x + PLAYERCOLL >= p3DBlock->GetPos().x - BLOCK_X
					&& pos.x - PLAYERCOLL <= p3DBlock->GetPos().x + BLOCK_X
					&& pos.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_Y
					&& pos.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y)
				{
					m_move.y = 0.0f;
					pos.y = p3DBlock->GetPos().y - RESETPOS;
				}
				//�u���b�N�̉E�ʂƓ���������
				if (pos.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_Y
					&& pos.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y
					&& m_PosOld.x - PLAYERCOLL > p3DBlock->GetPos().x - BLOCK_X
					&& pos.x - PLAYERCOLL <= p3DBlock->GetPos().x + BLOCK_X
					&& pos.y + PLAYERCOLL >= p3DBlock->GetPos().y - BLOCK_Y
					&& pos.y - PLAYERCOLL <= p3DBlock->GetPos().y + BLOCK_Y)
				{
					m_move.x = 0.0f;
					pos.x = p3DBlock->GetPos().x + RESETPOS;
				}

				//�u���b�N�̍��ʂƓ���������
				if (pos.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_Y
					&& pos.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y
					&& m_PosOld.x + PLAYERCOLL < p3DBlock->GetPos().x + BLOCK_X
					&& pos.x + PLAYERCOLL >= p3DBlock->GetPos().x - BLOCK_X
					&& pos.y + PLAYERCOLL >= p3DBlock->GetPos().y - BLOCK_Y
					&& pos.y - PLAYERCOLL <= p3DBlock->GetPos().y + BLOCK_Y)
				{
					m_move.x = 0.0f;
					pos.x = p3DBlock->GetPos().x - RESETPOS;
				}

				//Z���̔���͕K�v�Ȃ��̂ŃR�����g�A�E�g
				////�u���b�N�̉��ʂƓ���������
				//if (pos.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_Y
				//	&& m_PosOld.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y
				//	&& pos.x +PLAYERCOLL >= p3DBlock->GetPos().x - BLOCK_X
				//	&& pos.x -PLAYERCOLL <= p3DBlock->GetPos().x + BLOCK_X
				//	&& pos.y +PLAYERCOLL >= p3DBlock->GetPos().y - BLOCK_Y
				//	&& pos.y -PLAYERCOLL <= p3DBlock->GetPos().y + BLOCK_Y)
				//{
				//	m_move.z = 0.0f;
				//	pos.z = p3DBlock->GetPos().z - RESETPOS;
				//}

				////�u���b�N�̎�O�Ɠ���������
				//if (pos.z - PLAYERCOLL <= p3DBlock->GetPos().z + BLOCK_Y
				//	&& m_PosOld.z + PLAYERCOLL >= p3DBlock->GetPos().z - BLOCK_X
				//	&& pos.x + PLAYERCOLL >= p3DBlock->GetPos().x - BLOCK_X
				//	&& pos.x - PLAYERCOLL <= p3DBlock->GetPos().x + BLOCK_X
				//	&& pos.y + PLAYERCOLL >= p3DBlock->GetPos().y - BLOCK_Y
				//	&& pos.y - PLAYERCOLL <= p3DBlock->GetPos().y + BLOCK_Y)
				//{
				//	m_move.z = 0.0f;
				//	pos.z = p3DBlock->GetPos().z + RESETPOS;
				//}
			}
			//�v���C���[���m�̏Փ�
			if (type == CObject::TYPE::PLAYER01 || type == CObject::TYPE::PLAYER02)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;
				pPlayer->GetPos();

				//��
				if (pos.y - PLAYERCOLL <= pPlayer->GetPos().y + PLAYERCOLL
					&& m_PosOld.y - PLAYERCOLL > pPlayer->GetPos().y + PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pPlayer->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pPlayer->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= pPlayer->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pPlayer->GetPos().z + PLAYERCOLL)
				{
					m_Jump = true;
					m_move.y = 0.0f;
					pos.y = pPlayer->GetPos().y + (PLAYERCOLL * 2) + 1.0f;
				}
				//�v���C���[�̉��ʂɓ���������
				if (pos.y + PLAYERCOLL >= pPlayer->GetPos().y - PLAYERCOLL
					&& m_PosOld.y + PLAYERCOLL < pPlayer->GetPos().y - PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pPlayer->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pPlayer->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= pPlayer->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pPlayer->GetPos().z + PLAYERCOLL)
				{
					m_move.y = 0.0f;
					pos.y = pPlayer->GetPos().y - (PLAYERCOLL * 2) + 1.0f;
				}
				//�v���C���[�̉E�ʂƓ���������
				if (pos.z + PLAYERCOLL >= pPlayer->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pPlayer->GetPos().z + PLAYERCOLL
					&& m_PosOld.x - PLAYERCOLL > pPlayer->GetPos().x + PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pPlayer->GetPos().x + PLAYERCOLL
					&& pos.y + PLAYERCOLL >= pPlayer->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= pPlayer->GetPos().y + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					pos.x = pPlayer->GetPos().x + (PLAYERCOLL * 2) + 2.0f;
				}

				//�v���C���[�̍��ʂƓ���������
				if (pos.z + PLAYERCOLL >= pPlayer->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pPlayer->GetPos().z - PLAYERCOLL
					&& m_PosOld.x + PLAYERCOLL < pPlayer->GetPos().x + PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pPlayer->GetPos().x - PLAYERCOLL
					&& pos.y + PLAYERCOLL >= pPlayer->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= pPlayer->GetPos().y + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					pos.x = pPlayer->GetPos().x - (PLAYERCOLL * 2) - 2.0f;
				}
			}
			//�S�[���ɐG�ꂽ��
			else if (type == CObject::TYPE::GOAL)
			{
				CGoal* c3DGoal = (CGoal*)pObj;
				c3DGoal->GetPos();

				//�S�[���̏�ɓ���������
				if (pos.y - PLAYERCOLL <= c3DGoal->GetPos().y + PLAYERCOLL
					&& m_PosOld.y - PLAYERCOLL > c3DGoal->GetPos().y + PLAYERCOLL
					&& pos.x + PLAYERCOLL >= c3DGoal->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= c3DGoal->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= c3DGoal->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= c3DGoal->GetPos().z + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					m_move.y += 100.0f;
					m_Goalflag = true;
					m_Jump = true;
				}
				//�����瓖��������
				if (pos.y + PLAYERCOLL >= c3DGoal->GetPos().y - PLAYERCOLL
					&& m_PosOld.y + PLAYERCOLL < c3DGoal->GetPos().y - PLAYERCOLL
					&& pos.x + PLAYERCOLL >= c3DGoal->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= c3DGoal->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= c3DGoal->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= c3DGoal->GetPos().z + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					m_move.y += 2.2f;
					m_Goalflag = true;
				}
				//�E�Ɠ���������
				if (pos.z + PLAYERCOLL >= c3DGoal->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= c3DGoal->GetPos().z + PLAYERCOLL
					&& m_PosOld.x - PLAYERCOLL > c3DGoal->GetPos().x + PLAYERCOLL
					&& pos.x - PLAYERCOLL <= c3DGoal->GetPos().x + PLAYERCOLL
					&& pos.y + PLAYERCOLL >= c3DGoal->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= c3DGoal->GetPos().y + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					m_move.y += 2.2f;
					m_Goalflag = true;
				}

				//���Ɠ���������
				if (pos.z + PLAYERCOLL >= c3DGoal->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= c3DGoal->GetPos().z - PLAYERCOLL
					&& m_PosOld.x + PLAYERCOLL < c3DGoal->GetPos().x + PLAYERCOLL
					&& pos.x + PLAYERCOLL >= c3DGoal->GetPos().x - PLAYERCOLL
					&& pos.y + PLAYERCOLL >= c3DGoal->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= c3DGoal->GetPos().y + PLAYERCOLL)
				{
					m_move.x = 0.0f;
					m_move.y += 2.2f;
					m_Goalflag = true;
				}
			}
			//�A�C�e���̓����蔻��
			else if (type == CObject::TYPE::ITEM)
			{
				CItem* pItem = (CItem*)pObj;
				pItem->GetPos();

				bool bHit = false;
				if (pos.y - PLAYERCOLL <= pItem->GetPos().y + PLAYERCOLL
					&& m_PosOld.y - PLAYERCOLL > pItem->GetPos().y + PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pItem->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pItem->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= pItem->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pItem->GetPos().z + PLAYERCOLL)
				{
					bHit = true;
				}
				//�����瓖��������
				if (pos.y + PLAYERCOLL >= pItem->GetPos().y - PLAYERCOLL
					&& m_PosOld.y + PLAYERCOLL < pItem->GetPos().y - PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pItem->GetPos().x - PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pItem->GetPos().x + PLAYERCOLL
					&& pos.z + PLAYERCOLL >= pItem->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pItem->GetPos().z + PLAYERCOLL)
				{
					bHit = true;
				}
				//�E�Ɠ���������
				if (pos.z + PLAYERCOLL >= pItem->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pItem->GetPos().z + PLAYERCOLL
					&& m_PosOld.x - PLAYERCOLL > pItem->GetPos().x + PLAYERCOLL
					&& pos.x - PLAYERCOLL <= pItem->GetPos().x + PLAYERCOLL
					&& pos.y + PLAYERCOLL >= pItem->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= pItem->GetPos().y + PLAYERCOLL)
				{
					bHit = true;
				}

				//���Ɠ���������
				if (pos.z + PLAYERCOLL >= pItem->GetPos().z - PLAYERCOLL
					&& pos.z - PLAYERCOLL <= pItem->GetPos().z + PLAYERCOLL
					&& m_PosOld.x + PLAYERCOLL < pItem->GetPos().x - PLAYERCOLL
					&& pos.x + PLAYERCOLL >= pItem->GetPos().x - PLAYERCOLL
					&& pos.y + PLAYERCOLL >= pItem->GetPos().y - PLAYERCOLL
					&& pos.y - PLAYERCOLL <= pItem->GetPos().y + PLAYERCOLL)
				{
					bHit = true;
				}

				//����������
				if (bHit)
				{
					m_Itemflag = true;
					m_pSound_Player->PlaySound(CSound::SOUND_LABEL_POWERUP);
					pItem->Uninit();
				}

			}
		}
	}

	
	return pos;

}


//���[�h����
HRESULT CPlayer::Load()
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	CModel* pModel = CManager::GetModel();

	int nIdx = pModel->Regist("data\\xfile\\N_Player_01.x");
	pModel->GetAddress(nIdx);
	m_dwNumMat_Player[PLAYER_1_N_NOM] = pModel->GetAddress(nIdx).m_dwNumMat_Model;
	m_pBuffMat_Player[PLAYER_1_N_NOM] = pModel->GetAddress(nIdx).m_Buff_Model;
	m_pMesh_Player[PLAYER_1_N_NOM] = pModel->GetAddress(nIdx).m_Mesh_Model;

	nIdx = pModel->Regist("data\\xfile\\S_Player_01.x");
	pModel->GetAddress(nIdx);
	m_dwNumMat_Player[PLAYER_2_S_NOM] = pModel->GetAddress(nIdx).m_dwNumMat_Model;
	m_pBuffMat_Player[PLAYER_2_S_NOM] = pModel->GetAddress(nIdx).m_Buff_Model;
	m_pMesh_Player[PLAYER_2_S_NOM] = pModel->GetAddress(nIdx).m_Mesh_Model;

	nIdx = pModel->Regist("data\\xfile\\N_Player_02.x");
	pModel->GetAddress(nIdx);
	m_dwNumMat_Player[PLAYER_1_N_MAG] = pModel->GetAddress(nIdx).m_dwNumMat_Model;
	m_pBuffMat_Player[PLAYER_1_N_MAG] = pModel->GetAddress(nIdx).m_Buff_Model;
	m_pMesh_Player[PLAYER_1_N_MAG] = pModel->GetAddress(nIdx).m_Mesh_Model;

	nIdx = pModel->Regist("data\\xfile\\S_Player_02.x");
	pModel->GetAddress(nIdx);
	m_dwNumMat_Player[PLAYER_2_S_MAG] = pModel->GetAddress(nIdx).m_dwNumMat_Model;
	m_pBuffMat_Player[PLAYER_2_S_MAG] = pModel->GetAddress(nIdx).m_Buff_Model;
	m_pMesh_Player[PLAYER_2_S_MAG] = pModel->GetAddress(nIdx).m_Mesh_Model;

	return S_OK;
}

//�A�����[�h
void CPlayer::Unload()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		//���b�V���̔j��
		if (CPlayer::m_pMesh_Player[i] != nullptr)
		{
			CPlayer::m_pMesh_Player[i]->Release();
			CPlayer::m_pMesh_Player[i] = NULL;
		}

		//�}�e���A���̔j��
		if (CPlayer::m_pBuffMat_Player[i] != NULL)
		{
			CPlayer::m_pBuffMat_Player[i]->Release();
			CPlayer::m_pBuffMat_Player[i] = NULL;
		}
	}
}


void CPlayer::SetPlayerType(TYPEPLAYER type)
{
	m_TypePlayer = type;
}


void CPlayer::SetState_Block(PLAYER_BLOCK_ST state_B)
{
	m_PlayerState_Block = state_B;
}

CPlayer::TYPEPLAYER CPlayer::GetPlayerType()
{
	return m_TypePlayer;
}

CPlayer::PLAYER_BLOCK_ST CPlayer::GetState_Block()
{
	return m_PlayerState_Block;
}


//=======================================================================
//
//�v���C���[1
// 
//=======================================================================

HRESULT CPlayer1::Init()
{
	CPlayer::Init();
	CObject::SetType(TYPE::PLAYER01);

	return S_OK;
}
void CPlayer1::Update()
{

	if (m_Itemflag == true)
	{
		m_jumpPower = JUMP_INC * JUMP_INC_ITEMUSE;
	}
	else
	{
		m_jumpPower = JUMP_INC;
	}

	if (m_IsAbilityActive)
	{
		ApplyMovementModifier();
	}
	
	if (m_PlayerState == ALIVE && m_pos.y - 50.0f < 0.0f)
	{
		m_PlayerState = DEAD;
	}
	CPlayer::Update();
}

void CPlayer1::Draw()
{
	CPlayer::Draw();
	if (m_IsAbilityActive || m_Itemflag == true)
	{
		//�v���C���[1�i�A�r���e�B�������j
		BindMesh(m_pMesh_Player[PLAYER_1_N_MAG], m_pBuffMat_Player[PLAYER_1_N_MAG], m_dwNumMat_Player[PLAYER_1_N_MAG], m_pMaterial_Player, m_pTexture_Player[0]);
	}
	else
	{
		//�v���C���[1�i�ʏ펞�j
		BindMesh(m_pMesh_Player[PLAYER_1_N_NOM], m_pBuffMat_Player[PLAYER_1_N_NOM], m_dwNumMat_Player[PLAYER_1_N_NOM], m_pMaterial_Player, m_pTexture_Player[0]);
	}
}

//����
CPlayer1* CPlayer1::Create(D3DXVECTOR3 pos)
{
	CPlayer1* pPlayer1 = new CPlayer1;
	if (pPlayer1)
	{
		pPlayer1->Init();
		pPlayer1->Setpos(pos);
		pPlayer1->SetPlayerType(TYPEPLAYER::PLAYER_1);
	}
	

	for (int nCntmodel = 0; nCntmodel < 3; nCntmodel++)
	{
		for (int i = 0; i < (int)m_dwNumMat_Player[nCntmodel]; i++)
		{
			if (m_pTexture_Player[i] != nullptr)
			{
				pPlayer1->BindMesh(m_pMesh_Player[PLAYER_1_N_NOM], m_pBuffMat_Player[PLAYER_1_N_NOM], m_dwNumMat_Player[PLAYER_1_N_NOM], m_pMaterial_Player, m_pTexture_Player[i]);
			}
			else
			{
				pPlayer1->BindMesh(m_pMesh_Player[PLAYER_1_N_NOM], m_pBuffMat_Player[PLAYER_1_N_NOM], m_dwNumMat_Player[PLAYER_1_N_NOM], m_pMaterial_Player, m_pTexture_Player[i]);
			}
		}
	}

	pPlayer1->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	return pPlayer1;
}


//�v���C���[1�̃t���O�Ǘ�
void CPlayer1::ApplyMovementModifier()
{

	
	switch (m_PlayerState_Block)
	{
	case STATE_S_BLOCK:
	{
		m_move *= 0.5f;
		m_jumpPower = 8.0f;
		break;
	}
	case STATE_N_BLOCK:
	{
		m_move.x *= 1.5f;
		m_jumpPower = JUMP_INC_POWERUP;
		break;
	}
	default:

		m_jumpPower = JUMP_INC;
		break;
	}
}



//=======================================================================
//
//�v���C���[2
// 
//=======================================================================

//������
HRESULT CPlayer2::Init()
{

	CPlayer::Init();
	CObject::SetType(TYPE::PLAYER02);

	return S_OK;
}

//�X�V����
void CPlayer2::Update()
{
	
	if (m_Itemflag == true)
	{
		m_jumpPower = JUMP_INC * JUMP_INC_ITEMUSE;
	}
	else
	{
		m_jumpPower = JUMP_INC;
	}
	if (m_IsAbilityActive)
	{
		ApplyMovementModifier();
	}
	
	
	if (m_PlayerState == ALIVE && m_pos.y - 50.0f < 0.0f)
	{
		m_PlayerState = DEAD;
	}
	CPlayer::Update();
}

//�`�揈��
void CPlayer2::Draw()
{
	CPlayer::Draw();
	if (m_IsAbilityActive|| m_Itemflag == true)
	{
		//�v���C���[2�i�A�r���e�B�������j	
		BindMesh(m_pMesh_Player[PLAYER_2_S_MAG], m_pBuffMat_Player[PLAYER_2_S_MAG], m_dwNumMat_Player[PLAYER_2_S_MAG],	m_pMaterial_Player, m_pTexture_Player[0]);
	}
	else
	{
		//�v���C���[2�i�ʏ펞�j
		BindMesh(m_pMesh_Player[PLAYER_2_S_NOM], m_pBuffMat_Player[PLAYER_2_S_NOM], m_dwNumMat_Player[PLAYER_2_S_NOM], m_pMaterial_Player, m_pTexture_Player[0]);
	}
}

//����
CPlayer2* CPlayer2::Create(D3DXVECTOR3 pos)
{
	CPlayer2* pPlayer2 = new CPlayer2;

	pPlayer2->Init();
	pPlayer2->Setpos(pos);
	pPlayer2->SetPlayerType(TYPEPLAYER::PLAYER_2);

	for (int nCntmodel = 0; nCntmodel < 3; nCntmodel++)
	{
		for (int i = 0; i < (int)m_dwNumMat_Player[nCntmodel]; i++)
		{
			if (m_pTexture_Player[i] != nullptr)
			{
				pPlayer2->BindMesh(m_pMesh_Player[PLAYER_2_S_NOM], m_pBuffMat_Player[PLAYER_2_S_NOM], m_dwNumMat_Player[PLAYER_2_S_NOM], m_pMaterial_Player, m_pTexture_Player[i]);
			}
			else
			{
				pPlayer2->BindMesh(m_pMesh_Player[PLAYER_2_S_NOM], m_pBuffMat_Player[PLAYER_2_S_NOM], m_dwNumMat_Player[PLAYER_2_S_NOM], m_pMaterial_Player, m_pTexture_Player[i]);
			}
		}
	}
	pPlayer2->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	return pPlayer2;
}


//�v���C���[2�̃t���O�Ǘ�
void CPlayer2::ApplyMovementModifier()
{


	switch (m_PlayerState_Block)
	{
	case STATE_S_BLOCK:
	{
		m_move.x *= 1.5f;
		m_jumpPower = JUMP_INC_POWERUP;
		break;
	}
	case STATE_N_BLOCK:
	{
 		m_move *= 0.5f;
		m_jumpPower = 8.0f;
		break;
	}
	default:
		m_jumpPower = JUMP_INC;
		break;
	}
}