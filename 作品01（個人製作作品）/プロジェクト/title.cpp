//===============================================================================
//
// title.cpp
// 
//===============================================================================
#include "title.h"
#include "main.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"

#include "player.h"
#include "game.h"
#include "block.h"
#include "backblock.h"

#include "playermanager.h"
CSound* m_pSound_Title = nullptr;

CTitle::CTitle() {

}
CTitle::~CTitle() {

}

HRESULT CTitle::Init() {
	m_TutorialCreate = false;

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(D3DXVECTOR3(MAXPOS_X / 2 - 20.0f, 350.0f, 0.0f));
	

	m_pCamera = new CCamera();
	
	m_pCamera->Init();  // �e�V�[�����Ƃɏ�����
	
	m_PlayerManager = new CPlayerManager();

	

	TitleLoad();

	m_PlayerManager->Init();

	m_pSound_Title = CManager::GetSound();

	m_pSound_Title->PlaySound(CSound::SOUND_LABEL_BGM_01);
	return S_OK;
}

void CTitle::Uninit() {
	m_pSound_Title->StopSound();
	if (m_pCamera != nullptr) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	delete m_PlayerManager;
	m_PlayerManager = nullptr;
	if (m_pBg) {
		m_pBg->Uninit();
		
	}

}

void CTitle::Update() {
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();
	
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
		m_pSound_Title->PlaySound(CSound::SOUND_LABEL_CLICK);
	}

#ifdef DEBUG
	
	if (pKeyboard->GetKeyboardTrigger(DIK_F2) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_SELECT);
	}
#endif // !DEBUG

	
	
	m_pCamera->SetCamera();
	m_pCamera->Update();
	m_PlayerManager->Update();
}

void CTitle::Draw() {
	m_PlayerManager->Draw();
}

void CTitle::TitleLoad()
{
	//�u���b�N�̐�����v���C���[�̐��������������ˁI�I�I�I
	//��ԉ��̃u���b�N��+90.0�����Ȃ��Ƃ߂荞�݂܂�
	//����l�͏c�P�P�܂�
	// 0_�v���C���[1
	// 1_�v���C���[2
	// 2_TYPE_NOMALBLOCK,
	// 3_TYPE_S_BLOCK,
	// 4_TYPE_N_BLOCK,
	// 5_TYPE_MOVE_BLOCK_R,
	// 6_TYPE_MOVE_BLOCK_L,
	// 7_TYPE_GOAL
	// 8_TYPE_ITEM
	
	int nScanData = 100;//�ǂݍ��񂾃f�[�^
	int nScanData_X = 0;//�ǂݍ��񂾃f�[�^��X���W�p�ϐ�
	int nScanData_Y = 10;//�ǂݍ��񂾃f�[�^��Y���W�p�ϐ�

	FILE* pFile{};
	
	pFile = fopen(STAGE_TITLE, "r");
	

	if (pFile != NULL)//�t�@�C�����J������
	{
		while (1)
		{
			char aString[NUMBBLOCK] = {};
			fgets(aString, NUMBBLOCK, pFile);

			//======================================
			for (int i = 0; i < 50; i++)
			{
				if (aString[i] == '0')
				{
					//pPlayer = CPlayer::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f), CPlayer::PLAYER_1);
					m_PlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_1, D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f));

				}
				else if (aString[i] == '1')
				{
					//pPlayer = CPlayer::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f), CPlayer::PLAYER_2);
					m_PlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_2, D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f));

				}
				else if (aString[i] == '2')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_NOMALBLOCK);
				}
				else if (aString[i] == '3')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_S_BLOCK);
				}
				else if (aString[i] == '4')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_N_BLOCK);
				}
				else if (aString[i] == '5')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_MOVE_BLOCK_R);
				}
				else if (aString[i] == '6')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_MOVE_BLOCK_L);
				}
				else if (aString[i] == '7')
				{
					//�S�[��
					CGoal::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f));
				}
				else if (aString[i] == '8')
				{
					//�A�C�e��
					CItem::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f));
				}
				
			}

			nScanData_Y--;

			if (aString[0] == '#')
			{
				break;
			}
		}
	}
	else
	{
		return;
	}


	fclose(pFile);//�t�@�C�������

	
	{//�w�i�̃u���b�N�̐����i�����_���j
		srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

		for (int nBBlkcnt = 0; nBBlkcnt < NUMBBLOCK; nBBlkcnt++)
		{
			//0�`9�̗�����ݒ�
			int nBBlockpos_X = rand() % 200 + 1;
			int nBBlockpos_Z = rand() % 4000 + 2000;
			int nScale_X = rand() % 5 + 2;
			int nScale_Y = rand() % 10 + 1;
			int nScale_Z = rand() % 5 + 2;

			//�u���b�N�̎�ނ������_���ɐݒ�
			int nBBlockType = rand() % 5;

			if (nBBlockType == 0)
			{//�u���b�N�^�C�v1�𐶐�
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_01, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 1)
			{//�u���b�N�^�C�v2�𐶐�
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_02, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 2)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_03, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 3)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_04, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 4)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_05, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
		}
	}
}