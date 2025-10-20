//========================================================
//
//playablesene.cpp
//Auther:Satoshikuramae
// 
//========================================================
#include "playablesene.h"


//デストラクタ
CPlayableScene::~CPlayableScene()
{
	delete m_pPlayerManager;
	m_pPlayerManager = nullptr;
	delete m_pBlock;
	m_pBlock = nullptr;
}

//更新処理
void CPlayableScene::Update()
{
	m_pPlayerManager->Update();
}

//描画処理
void CPlayableScene::Draw()
{
	m_pPlayerManager->Draw();
}

//ステージ読み込み
void CPlayableScene::LoadStage(const char* filePath)
{
	//ブロックの生成やプレイヤーの生成
	//一番下のブロックは+90.0ｆしないとめり込みます
	//上限値は縦１１個まで
	// 0_プレイヤー1
	// 1_プレイヤー2
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
	int nScanData_Y = 0; // ステージの高さ方向インデックス

	// ファイルの行数を調べる
	std::vector<std::string> lines;
	while (fgets(line, sizeof(line), pFile))
	{
		if (line[0] == '#') break;
		lines.push_back(line);
	}

	fclose(pFile);

	//下から生成するためファイル行数-1の値をnScanData_Yに代入する
	if (!lines.empty())
	{
		nScanData_Y = static_cast<int>(lines.size()) - 1;
	}
	else
	{
		nScanData_Y = 0; // ファイルが空ならY=0扱い
		return;
	}

	for (int y = 0; y < lines.size(); y++)
	{
		//読み込み時「"」等を読み込んでバグが起こらないように削除を行う
		std::string currentLine = lines[y];
		std::stringstream ss(currentLine);
		std::string cell;

		int x = 0;
		while (std::getline(ss, cell, ','))  // カンマで区切る
		{
			std::string cell_trimmed = cell;

			// 前後の空白・改行などを削除
			cell_trimmed.erase(0, cell_trimmed.find_first_not_of(" \t\r\n"));
			cell_trimmed.erase(cell_trimmed.find_last_not_of(" \t\r\n") + 1);

			// BOM除去（UTF-8ファイルの場合に先頭で発生することがある）
			if (cell_trimmed.size() >= 3 &&
				(unsigned char)cell_trimmed[0] == 0xEF &&
				(unsigned char)cell_trimmed[1] == 0xBB &&
				(unsigned char)cell_trimmed[2] == 0xBF) {
				cell_trimmed = cell_trimmed.substr(3);
			}

			// 空欄ならスキップ
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

		nScanData_Y--;		//20→19→18…のように減らすことで下から生成

		if (cell == "#")
		{
			break;
		}
	}
	//==================================================================================



	{//背景のブロックの生成（ランダム）
		srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

		for (int nBBlkcnt = 0; nBBlkcnt < NUMBBLOCK; nBBlkcnt++)
		{
			//0～9の乱数を設定
			int nBBlockpos_X = rand() % 200 + 1;
			int nBBlockpos_Z = rand() % 4000 + 2000;
			int nScale_X = rand() % 5 + 2;
			int nScale_Y = rand() % 10 + 1;
			int nScale_Z = rand() % 5 + 2;

			//ブロックの種類をランダムに設定
			int nBBlockType = rand() % 5;

			if (nBBlockType == 0)
			{//ブロックタイプ1を生成
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_01, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 1)
			{//ブロックタイプ2を生成
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_02, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 2)
			{//ブロックタイプ3を生成
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_03, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 3)
			{//ブロックタイプ3を生成
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_04, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
			else if (nBBlockType == 4)
			{//ブロックタイプ3を生成
				CBackBlock::Create(D3DXVECTOR3((float)nBBlkcnt * nBBlockpos_X, -1000.0f, (float)nBBlockpos_Z),
					CBackBlock::BACKBLOCK_05, D3DXVECTOR3(nScale_X * 10.0f, nScale_Y * 5.0f, nScale_Z * 10.0f));
			}
		}
	}
}