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

//�R���X�g���N�^
CTitle::CTitle() 
{

}

//�f�X�g���N�^
CTitle::~CTitle() 
{

}

//����������
HRESULT CTitle::Init()
{
	m_TutorialCreate = false;

	m_pBg = new CBg();
	m_pBg->Init();

	m_pBg->Create(TITLEUI_POS);
	
	m_pCamera = new CCamera();
	
	m_pCamera->Init(); 

	TitleLoad();

	m_pSound_Title = CManager::GetSound();

	m_pSound_Title->PlaySound(CSound::SOUND_LABEL_BGM_01);

	return S_OK;
}

//�I������
void CTitle::Uninit() 
{
	m_pSound_Title->StopSound();
	if (m_pCamera != nullptr) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	
	if (m_pBg) {
		m_pBg->Uninit();
		
	}
}

//�X�V����
void CTitle::Update() 
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();
	
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
		m_pSound_Title->PlaySound(CSound::SOUND_LABEL_CLICK);
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_F2) == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE::MODE_SELECT);
	}

	m_pCamera->SetCamera();
	m_pCamera->Update();
	CPlayableScene::Update();
}

//�`�揈��
void CTitle::Draw() 
{
	CPlayableScene::Draw();
}

//�X�e�[�W�ǂݍ��ݏ���
void CTitle::TitleLoad()
{
	LoadStage(TITLESTAGE);
}