//===============================================================================
//
//scene.cpp
// 
//Author Kuramaesatoshi
// 
// TODO �X�e�[�W�ǂݍ��ݏ�������ɂ܂Ƃ߂�A���@�𐶐�����V�[����p��Scene�N���X�𐧒肷��
//===============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "stageselect.h"
#include "tutorial.h"

CScene::MODE CScene::m_Mode = CScene::MODE_TITLE;

//�R���X�g���N�^
CScene::CScene() 
{

}

//�f�X�g���N�^
CScene::~CScene() 
{

}

HRESULT CScene::Init() 
{

	return S_OK;
}

//�I������
void CScene::Uninit() 
{

}
//�X�V����
void CScene::Update() 
{

}
//�`�揈��
void CScene::Draw()
{

}

//����
CScene* CScene::Create(MODE mode) 
{

	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle();
		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial();
		break;
	case MODE_SELECT:
		pScene = new CStageselect();
		break;
	case MODE_GAME:
		pScene = new CGame();
		break;
	case MODE_RESULT_CLEAR:
		pScene = new CResult();
		break;
	case MODE_RESULT_GAMEOVER:
		pScene = new CResult();
		break;
	}
	
	m_Mode = mode;
	pScene->Init();
	return pScene;
}

//�V�[���擾
CScene::MODE CScene::GetScene()
{
	return m_Mode;
}

