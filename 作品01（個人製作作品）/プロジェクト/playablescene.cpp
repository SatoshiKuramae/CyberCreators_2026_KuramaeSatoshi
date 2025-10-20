//========================================================
//
//playablesene.cpp
//Auther:Satoshikuramae
// 
//========================================================
#include "playablesene.h"


//�f�X�g���N�^
CPlayableScene::~CPlayableScene()
{
	delete m_pPlayerManager;
	m_pPlayerManager = nullptr;
	delete m_pBlock;
	m_pBlock = nullptr;
}

//�X�V����
void CPlayableScene::Update()
{
	m_pPlayerManager->Update();
}

//�`�揈��
void CPlayableScene::Draw()
{
	m_pPlayerManager->Draw();
}

//�X�e�[�W�ǂݍ���
void CPlayableScene::LoadStage(const char* filePath)
{
	//�u���b�N�̐�����v���C���[�̐���
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

	//==================================================================================

	m_pPlayerManager = new CPlayerManager();
	m_pPlayerManager->Init();


	FILE* pFile = fopen(filePath, "r");
	if (!pFile) return;

	char line[1024];
	int nScanData_Y = 0; // �X�e�[�W�̍��������C���f�b�N�X

	// �t�@�C���̍s���𒲂ׂ�
	std::vector<std::string> lines;
	while (fgets(line, sizeof(line), pFile))
	{
		if (line[0] == '#') break;
		lines.push_back(line);
	}

	fclose(pFile);

	//�����琶�����邽�߃t�@�C���s��-1�̒l��nScanData_Y�ɑ������
	if (!lines.empty())
	{
		nScanData_Y = static_cast<int>(lines.size()) - 1;
	}
	else
	{
		nScanData_Y = 0; // �t�@�C������Ȃ�Y=0����
		return;
	}

	for (int y = 0; y < lines.size(); y++)
	{
		//�ǂݍ��ݎ��u"�v����ǂݍ���Ńo�O���N����Ȃ��悤�ɍ폜���s��
		std::string currentLine = lines[y];
		std::stringstream ss(currentLine);
		std::string cell;

		int x = 0;
		while (std::getline(ss, cell, ','))  // �J���}�ŋ�؂�
		{
			std::string cell_trimmed = cell;

			// �O��̋󔒁E���s�Ȃǂ��폜
			cell_trimmed.erase(0, cell_trimmed.find_first_not_of(" \t\r\n"));
			cell_trimmed.erase(cell_trimmed.find_last_not_of(" \t\r\n") + 1);

			// BOM�����iUTF-8�t�@�C���̏ꍇ�ɐ擪�Ŕ������邱�Ƃ�����j
			if (cell_trimmed.size() >= 3 &&
				(unsigned char)cell_trimmed[0] == 0xEF &&
				(unsigned char)cell_trimmed[1] == 0xBB &&
				(unsigned char)cell_trimmed[2] == 0xBF) {
				cell_trimmed = cell_trimmed.substr(3);
			}

			// �󗓂Ȃ�X�L�b�v
			if (cell_trimmed.empty()) {
				x++;
				continue;
			}

			int blockType = atoi(cell.c_str());
			D3DXVECTOR3 pos(x * BLOCKSIZE + STARTPOS, nScanData_Y * BLOCKSIZE, 0.0f);

			switch (blockType)
			{
			case 0:
				m_pPlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_1, pos);
				break;
			case 1:
				m_pPlayerManager->Create(CPlayerManager::TYPEPLAYER::PLAYER_2, pos);
				break;
			case 2:
				m_pBlock->Create(pos, CBlock::TYPE_NOMALBLOCK);
				break;
			case 3:
				m_pBlock->Create(pos, CBlock::TYPE_S_BLOCK);
				break;
			case 4:
				m_pBlock->Create(pos, CBlock::TYPE_N_BLOCK);
				break;
			case 5:
				m_pBlock->Create(pos, CBlock::TYPE_MOVE_BLOCK_R);
				break;
			case 6:
				m_pBlock->Create(pos, CBlock::TYPE_MOVE_BLOCK_L);
				break;
			case 7:
				CGoal::Create(pos);
				break;
			case 8:
				CItem::Create(pos);
				break;
			}

			x++;
		}

		nScanData_Y--;		//20��19��18�c�̂悤�Ɍ��炷���Ƃŉ����琶��

		if (cell == "#")
		{
			break;
		}
	}
	//==================================================================================



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