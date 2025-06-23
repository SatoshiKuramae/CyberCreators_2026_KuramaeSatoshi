//===============================================================================
//
// game.cpp
// Author:Satoshi Kuramae
// 
//===============================================================================
#include "game.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "block.h"
#include "floor.h"
#include "goal.h"
#include "backblock.h"
#include "stageselect.h"
#include "time.h"
#include "bg.h"
#include "item.h"

bool meshuse;

CGame* m_pTime = nullptr;
CGame* m_pNumplayer = nullptr;
CSound* m_pSound_Game = nullptr;

//�R���X�g���N�^
CGame::CGame() {
	m_bPouse = false;
}

//�f�X�g���N�^
CGame::~CGame() {

}

//����������
HRESULT CGame::Init() {
	meshuse = false;
	m_bPouse = false;
	m_pSound_Game = CManager::GetSound();
	if (m_pTime == nullptr && m_pNumplayer == nullptr)
	{
		m_pTime = new CTime;
		m_pNumplayer = new CNumplayer;
	}

	m_pTime->Init();

	m_pCamera = new CCamera();
	m_pCamera->Init();  // �e�V�[�����Ƃɏ�����

	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(D3DXVECTOR3(MAXPOS_X / 2, MAXPOS_Y / 2, 0.0f));

	m_PlayerManager = new CPlayerManager();

	LoadStage();
	m_PlayerManager->Init();

	m_pNumplayer->Init();

	m_pGauge = new CGauge();
	m_pGaugeframe = new CGaugeframe();

	m_pGauge->Init();
	m_pGaugeframe->Init();


	m_pGauge->Create(D3DXVECTOR3(1010.0f, 650.0f, 0.0f));
	m_pGaugeframe->Create(D3DXVECTOR3(1010.0f, 650.0f, 0.0f));

	if (CStageselect::GetStageSelect() == 1)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_01);
	}
	if (CStageselect::GetStageSelect() == 2)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_02);
	}
	if (CStageselect::GetStageSelect() == 3)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_03);
	}
	if (CStageselect::GetStageSelect() == 4)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_04);
	}
	if (CStageselect::GetStageSelect() == 5)
	{
		m_pSound_Game->PlaySound(CSound::SOUND_LABEL_GAMEBGM_05);
	}
	return S_OK;
}

//�I������
void CGame::Uninit() {

	m_pSound_Game->StopSound();
	m_pTime->Uninit();
	m_pNumplayer->Uninit();

	if (m_pCamera != nullptr) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pBg) {
		m_pBg->Uninit();
	}

	delete m_PlayerManager;
	m_PlayerManager = nullptr;

	m_pGauge->Uninit();
	m_pGaugeframe->Uninit();
}

//�X�V����
void CGame::Update() {
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	m_pTime->Update();
	
	
	m_pCamera->SetCamera();
	m_pCamera->Update();

	m_PlayerManager->Update();

	m_pNumplayer->Update();
	m_pGauge->Update();
#ifndef DEBUG
	if (pKeyboard->GetKeyboardPress(DIK_P) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_RESULT_CLEAR);
	}
#endif // !DEBUG

	
}

void CGame::Draw() {
	m_PlayerManager->Draw();
	m_pGauge->Draw();
	m_pGaugeframe->Draw();
}

//�X�e�[�W�̐�������
void CGame::LoadStage()
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
	CPlayer* pPlayer;
	

	int nScanData = 100;//�ǂݍ��񂾃f�[�^
	int nScanData_X = 0;//�ǂݍ��񂾃f�[�^��X���W�p�ϐ�
	int nScanData_Y = 10;//�ǂݍ��񂾃f�[�^��Y���W�p�ϐ�

	FILE* pFile{};

	//�ǂ̃X�e�[�W���I�΂�Ă��邩�ɂ�ĊJ���t�@�C����ς���
	if (CStageselect::GetStageSelect() == 1)
	{
		
		pFile = fopen(STAGE1, "r");
	}
	else if (CStageselect::GetStageSelect() == 2)
	{
		
		pFile = fopen(STAGE2, "r");
	}
	else if (CStageselect::GetStageSelect() == 3)
	{

		pFile = fopen(STAGE3, "r");
	}
	else if (CStageselect::GetStageSelect() == 4)
	{
		
		pFile = fopen(STAGE4, "r");
	}
	else if (CStageselect::GetStageSelect() == 5)
	{
		
		pFile = fopen(STAGE5, "r");
	}

	
	if (pFile != NULL)//�t�@�C�����J������
	{
		while (1)
		{
			char aString[NUMBBLOCK] = {};
			fgets(aString, NUMBBLOCK, pFile);

			
			for (int i = 0; i < NUMBBLOCK; i++)
			{
				if (aString[i] == '0')
				{
					m_PlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_1, D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f));
				}
				else if (aString[i] == '1')
				{
					m_PlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_2, D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE + 50.0f, 0.0f));
				}
				else if (aString[i] == '2')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE+ STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_NOMALBLOCK);
				}
				else if (aString[i] == '3')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE+ STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_S_BLOCK);
				}
				else if (aString[i] == '4')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE+ STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_N_BLOCK);
				}
				else if (aString[i] == '5')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE+ STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_MOVE_BLOCK_R);
				}
				else if (aString[i] == '6')
				{
					CBlock::Create(D3DXVECTOR3(i * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f), CBlock::TYPE_MOVE_BLOCK_L);
				}
				else if (aString[i] == '7')
				{
					//�S�[��
					CGoal::Create(D3DXVECTOR3(i * BLOCKSIZE+ STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f));
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

	CFloor::Create(D3DXVECTOR3(-200.0f, -500.0f, 1200.0f));
	CFloor::Create(D3DXVECTOR3(1000.0f, -500.0f, 1200.0f));
	CFloor::Create(D3DXVECTOR3(2000.0f, -500.0f, 1200.0f));

	//�w�i�̃u���b�N�̐����i�����_���j
		srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	
		for (int nBBlkcnt = 0; nBBlkcnt < NUMBBLOCK; nBBlkcnt++)
		{
			//0�`9�̗�����ݒ�
			int nBBlockpos_X = rand() % 300 + 1;
			int nBBlockpos_Z = rand() % 4000+2000;
			int nScale_X = rand() % 5 + 2;
			int nScale_Y = rand() % 10 + 1;
			int nScale_Z = rand() % 5 + 2;

			//�u���b�N�̎�ނ������_���ɐݒ�
			int nBBlockType = rand() % 5;

			if (nBBlockType == 0)
			{//�u���b�N�^�C�v1�𐶐�
				CBackBlock::Create(D3DXVECTOR3(nBBlkcnt * nBBlockpos_X , -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_01, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if(nBBlockType == 1)
			{//�u���b�N�^�C�v2�𐶐�
				CBackBlock::Create(D3DXVECTOR3(nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_02, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 2)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3(nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_03, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 3)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3(nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_04, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 4)
			{//�u���b�N�^�C�v3�𐶐�
				CBackBlock::Create(D3DXVECTOR3(nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_05, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
		}
	
}

void CGame::GetPause(bool bPause)
{
	bPause = m_bPouse;
}
