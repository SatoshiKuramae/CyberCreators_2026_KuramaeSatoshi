//============================================================
//
//playablesene.h
//Author Kuramaesatoshi
// 
//============================================================
#ifndef _PLAYABLESCENE_H_
#define _PLAYABLESCENE_H_
#include "scene.h"
#include "playermanager.h"
#include "block.h"
#include "backblock.h"

#include <iostream>
#include <fstream>
#include <sstream>
constexpr float  BLOCKSIZE(160.0f);
constexpr float  STARTPOS(2100.0f);
constexpr int NUMBBLOCK(500);
constexpr const char* TITLESTAGE = "data\\csvfile\\titlestage.csv";
constexpr const char* TUTORIALSTAGE = "data\\csvfile\\tutorialstage.csv";
constexpr const char* STAGE1 = "data\\csvfile\\stage01.csv";
constexpr const char* STAGE2 = "data\\csvfile\\stage02.csv";
constexpr const char* STAGE3 = "data\\csvfile\\stage03.csv";
constexpr const char* STAGE4 = "data\\csvfile\\stage04.csv";
constexpr const char* STAGE5 = "data\\csvfile\\stage05.csv";

static const D3DXVECTOR3 GAUGE_POS(1005.0f, 650.0f, 0.0f);
static const D3DXVECTOR3 GAUGEFLAME_POS(1010.0f, 650.0f, 0.0f);
//自機とブロックの生成を行うシーン専用の親Sceneクラス
class CPlayableScene : public CScene {
public:
	//シーンごとに独自の初期化を行うためデストラクタのみ共通
	virtual ~CPlayableScene();

	//ステージ読み込み処理
	virtual void LoadStage(const char* filePath);

	virtual void Update()override;
	virtual void Draw()override;
protected:
	CPlayerManager* m_pPlayerManager = nullptr;
	CBlock* m_pBlock = nullptr;
};
#endif