//==============================================================
//
// manager.cpp
//
//==============================================================

#include<Windows.h>
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "bg.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "floor.h"
#include "objectX.h"
#include "player.h"
#include "block.h"
#include "background.h"
#include "backblock.h"

//�ÓI�����o������
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CInputGamepad* CManager::m_pJoypad = nullptr;
//CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CFade* CManager::m_pFade = nullptr;
CModel* CManager::m_pModel = nullptr;
CSound* CManager::m_pSound = nullptr;
CGameprogress* CManager::m_pGameState = new CGameprogress();

//�R���X�g���N�^
CManager::CManager()
{

}
//�f�X�g���N�^
CManager::~CManager()
{

}

//������
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pScene = new CScene();
	m_pScene->Init();
	//�����_���[�̐���
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�̐���
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	// �W���C�p�b�h�̐���
	m_pJoypad = new CInputGamepad();
	m_pJoypad->Init(hInstance, hWnd);

	//�J��������
	/*m_pCamera = new CCamera();
	m_pCamera->Init();*/

	//���C�g����
	m_pLight = new CLight();
	m_pLight->Init();

	//�e�N�X�`���̐���
	m_pTexture = new CTexture();

	//���f���̐���
	m_pModel = new CModel();

	//�T�E���h������
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	m_pFade = new CFade();
	m_pFade->Init();

	

	//�ォ�珇�ɕ`�悳���
	CBg::Load();
	CBackBlock::Load();
	CPlayer::Load();
	CBlock::Load();
	CEnemy::Load();
	CExplosion::Load();
	CBullet::Load();
	CFloor::Load();

	//�ŏ��̃V�[���̐ݒ�

	m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	
	
	return S_OK;
}

//�I������
void CManager::Uninit()
{
	CBg::Unload();
	CBackBlock::Unload();
	CEnemy::Unload();
	CBlock::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CFloor::Unload();
	
	CTexture::Unload();
	CModel::Unload();
	if (m_pRenderer != nullptr)
	{
		m_pScene->Uninit();
		m_pKeyboard->Uninit();
		m_pRenderer->Uninit();
		m_pJoypad->Uninit();
		m_pFade->Uninit();
		m_pSound->Uninit();
		m_pTexture->Unload();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	CObject::ReleaseAll();
}

//�X�V����
void CManager::Update()
{
	m_pRenderer->Update();
	m_pScene->Update();
	m_pKeyboard->Update();
	m_pJoypad->Update();
	//m_pCamera->Update();
	m_pFade->Update();
}

//�`�揈��
void CManager::Draw()
{
	m_pRenderer->Draw();
	m_pFade->Draw();
	m_pScene->Draw();
}

void CManager::SetMode(CScene::MODE mode)
{
	//�I������
	if (m_pScene != nullptr)
	{
		//m_pCamera->Init();
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (mode == CScene::MODE::MODE_TITLE)
	{
		m_pGameState->Reset();
	}

	CObject::ReleaseAll();
	//����
	m_pScene = CScene::Create(mode);
}

//�����_���[�擾
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//�L�[�{�[�h�擾
CInputKeyboard* CManager::GetKeyboard(){
	return m_pKeyboard;
}

//�W���C�p�b�h�擾
CInputGamepad* CManager::GetJoypad(){
	return m_pJoypad;
}
//�J�����̎擾
//CCamera* CManager::GetCamera()
//{
//	return m_pCamera;
//}

//���C�g�̎擾
CLight* CManager::GetLight()
{
	return m_pLight;
}

//�V�[���̎擾
CScene* CManager::GetScene()
{
	return m_pScene;
}

CTexture* CManager::GetTexture() 
{
	return m_pTexture;
}

CFade* CManager::GetFade()
{
	return m_pFade;
}

CModel* CManager::GetModel()
{
	return m_pModel;
}

CSound* CManager::GetSound()
{
	return m_pSound;
}

CGameprogress* CManager::GetGameProgress() {
	return m_pGameState;
}