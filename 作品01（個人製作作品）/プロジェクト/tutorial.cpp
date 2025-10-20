//===============================================================================
//
// Tutorial.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "tutorial.h"
#include "main.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"

#include "player.h"
#include "game.h"
#include "block.h"
#include "backblock.h"


CSound* m_pSound_Tutorial = nullptr;

//�R���X�g���N�^
CTutorial::CTutorial() 
{

}

//�f�X�g���N�^
CTutorial::~CTutorial() 
{

}

//������
HRESULT CTutorial::Init() 
{
	m_pCamera = new CCamera();

	m_pCamera->Init();  // �e�V�[�����Ƃɏ�����

	TutorialLoad();


	m_pBg = new CBg();
	m_pBg->Init();
	m_pBg->Create(TUTORIALUI_POS);

	m_pNumplayer = new CNumplayer();
	m_pNumplayer->Init();
	m_pGauge = new CGauge();
	m_pGaugeframe = new CGaugeframe();

	m_pGauge->Init();
	m_pGaugeframe->Init();

	m_pTutorialUI = new CTutorialUI;
	m_pTutorialUI->Init();
	m_pTutorialUI->Create(TUTORIALUI_POS);

	m_pGauge->Create(GAUGE_POS);
	m_pGaugeframe->Create(GAUGEFLAME_POS);
	
	m_pSound_Tutorial = CManager::GetSound();
	m_pSound_Tutorial->PlaySound(CSound::SOUND_LABEL_BGM_01);

	return S_OK;
}

//�I������
void CTutorial::Uninit() 
{
	m_pSound_Tutorial->StopSound();
	if (m_pCamera != nullptr)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pBg)
	{
		m_pBg->Uninit();
	}
	m_pGauge->Uninit();
	m_pGaugeframe->Uninit();
	m_pNumplayer->Uninit();
	m_pTutorialUI->Uninit();
}

//�X�V����
void CTutorial::Update()
{

	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	{
		m_pSound_Tutorial->PlaySound(CSound::SOUND_LABEL_CLICK);
		CManager::GetFade()->SetFade(CScene::MODE::MODE_SELECT);

	}
	if (pKeyboard->GetKeyboardTrigger(DIK_F2) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_SELECT);
	}


	m_pCamera->SetCamera();
	m_pCamera->Update();
	CPlayableScene::Update();
	
	
	m_pGauge->Update();
	m_pNumplayer->Update();
	m_pTutorialUI->Update();
	
}

//�`�揈��
void CTutorial::Draw()
{
	CPlayableScene::Draw();
	m_pGauge->Draw();
	m_pGaugeframe->Draw();
	m_pTutorialUI->Draw();
}

//�X�e�[�W�ǂݍ���
void CTutorial::TutorialLoad()
{
	LoadStage(TUTORIALSTAGE);
}