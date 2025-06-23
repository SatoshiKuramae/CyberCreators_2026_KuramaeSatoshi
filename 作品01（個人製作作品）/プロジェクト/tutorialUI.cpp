
//===============================================================================
//
//tutorialUI.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "main.h"
#include "bg.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "background.h"
#include "tutorialUI.h"


//�R���X�g���N�^
CTutorialUI::CTutorialUI(int nPriority) :CObject2D(nPriority)
{

}

//�f�X�g���N�^
CTutorialUI::~CTutorialUI()
{

}

//�������i���_�o�b�t�@�����j
HRESULT CTutorialUI::Init()
{
	CTexture* pTex = CManager::GetTexture();
	CScene* pScene = nullptr;
	m_bCreateTutorial = false;
	m_tutorialcnt = 0;

	m_pTextureTutorial[0] = pTex->Regist("data\\texture\\tutorial01.png");
	m_pTextureTutorial[1] = pTex->Regist("data\\texture\\tutorial02.png");

	m_pSound_TutorialUI = CManager::GetSound();

	m_pSound_TutorialUI->PlaySound(CSound::SOUND_LABEL_BGM_01);
	//CObject2D::BindTexture(pTex->GetAddress(m_pTextureTutorial[1]), D3DXVECTOR2(1, 1));

	CObject2D::Init();

	return S_OK;
}

//�I��(���_�o�b�t�@�j��)
void CTutorialUI::Uninit()
{
	m_pSound_TutorialUI->StopSound();
	CObject2D::Uninit();
}

//�X�V����(���_�o�b�t�@�̍X�V)
void CTutorialUI::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputGamepad* pJoypad = CManager::GetJoypad();
	CTexture* pTex = CManager::GetTexture();

	
	if (pKeyboard->GetKeyboardTrigger(DIK_E) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_A)==true)
	{
		m_tutorialcnt++;
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_Q) == true|| pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_X)==true)
	{
		m_tutorialcnt--;
	}
	if (m_tutorialcnt > 1)
	{
		m_tutorialcnt = 1;
	}
	else if (m_tutorialcnt < 0)
	{
		m_tutorialcnt = 0;
	}
	CObject2D::BindTexture(pTex->GetAddress(m_pTextureTutorial[m_tutorialcnt]), D3DXVECTOR2(1, 1));
	
	if (m_tutorialcnt && pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_START) == true)
	{
		m_pSound_TutorialUI->PlaySound(CSound::SOUND_LABEL_CLICK);

		CManager::GetFade()->SetFade(CScene::MODE::MODE_SELECT);
	}
	
	CObject2D::Update();
}

//�`��i�|���S���`��j
void CTutorialUI::Draw()
{
	CObject2D::Draw();
}

//Object2D����
CTutorialUI* CTutorialUI::Create(D3DXVECTOR3 pos)
{
	CTutorialUI* pCTutorialUI = new CTutorialUI;
	pCTutorialUI->Setpos(pos);
	pCTutorialUI->SetParam(SCREEN_WIDTH, SCREEN_HEIGHT);
	pCTutorialUI->Init();
	pCTutorialUI->SetAnim(0.0f, 1.0f);
	pCTutorialUI->m_bCreateTutorial = true;
	return pCTutorialUI;
}
