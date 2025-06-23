//===============================================================================
//
//Playermanager.cpp
// 
//Author Kuramaesatoshi
//===============================================================================
#include "playermanager.h"
#include "input.h"
#include "manager.h"
#include "player.h"

//����������
void CPlayerManager::Init()
{
	m_pCurrentControlPlayer = m_pPlayer1;

}

//�I������
void CPlayerManager::Uninit()
{
    if (m_pPlayer1)m_pPlayer1->Uninit();
    if (m_pPlayer2)m_pPlayer2->Uninit();
}

//�X�V����
void CPlayerManager::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputGamepad* pJoypad = CManager::GetJoypad();
    CGameprogress* pProgress = CManager::GetGameProgress();
    float Gauge = pProgress->GetAbilityGauge();
    SwitchPlayer();

    if (m_pCurrentControlPlayer) {
        m_pCurrentControlPlayer->Playermove(); // ����\���̂�
    }
    if (pKeyboard->GetKeyboardPress(DIK_M) == true || pJoypad->GetJoypadPress(CInputGamepad::JOYKEY_RB) == true)
    {
        m_UseAbility = true;
        //�Q�[�W���l�ɂ���ĕω�����
        if (Gauge > 0.0f)
        {
            //�Q�[�W������Ƃ�
            pProgress->DecreaseAbilityGauge(0.5);
            if (m_pCurrentControlPlayer) {
                m_pCurrentControlPlayer->SetAbilityActive(true);
            }
        }
        else
        {
            //�Q�[�W���Ȃ��Ȃ�����
            if (m_pCurrentControlPlayer) {
                m_pCurrentControlPlayer->SetAbilityActive(false);
            }
        }
    }
    else
    {
        m_UseAbility = false;
        pProgress->IncreaseAbilityGauge(1.0);
        if (m_pCurrentControlPlayer) {
            m_pCurrentControlPlayer->SetAbilityActive(false);
        }
    }

    CPlayer* pActive = m_pCurrentControlPlayer;
    CPlayer* pInactive = (pActive == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

    if (pActive->IsAbilityActive()) {
        // �A�r���e�B�������͔񑀍쑤�̏d��OFF
        pInactive->SetEnableGravity(false);
    }
    else {
        // �A�r���e�B�������Ȃ�ʏ�ʂ�d��ON
        pInactive->SetEnableGravity(true);
    }

    

    // �A�r���e�B�������ł���Δ񑀍�v���C���[�������t����
    if (m_pCurrentControlPlayer && m_pCurrentControlPlayer->IsAbilityActive()) {
        CPlayer* pInactive = (m_pCurrentControlPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

        if (pInactive) {

            D3DXVECTOR3 from = pInactive->GetPos();
            D3DXVECTOR3 to = m_pCurrentControlPlayer->GetPos();

            D3DXVECTOR3 direction = to - from;
            float pullSpeed_X = 10.0f;  // �z�����x�͒�߂ň��肵�₷���Ȃ�
            float pullSpeed_Y = 10.0f;

            // �v���C���[���m���߂Â������Ȃ��悤���S������݂���i�d�v�j
            float dist = D3DXVec3Length(&direction);
            if (dist < PLAYER_RADIUS) {
                pInactive->SetMove(D3DXVECTOR3(0, 0, 0));  // �z������
                return;
            }

            D3DXVec3Normalize(&direction, &direction);
            D3DXVECTOR3 pullMove = direction * 25.0f;  // �z�����x

            // �z���ɂ��ړ��� move �ɃZ�b�g
            pInactive->SetMove(pullMove);
        }
    }


    CheckDeath(m_pPlayer1);
    CheckDeath(m_pPlayer2);

    //�v���C���[�̎��S�t���O�����m
    if (m_pCurrentControlPlayer && m_pPlayer1->IsDead() == true|| m_pPlayer2->IsDead()==true)
    {
        //�}�l�[�W���[���ł͂P�x�̂ݒʂ�悤��
        if (!m_IsDeathProcessed)
        {
            m_IsDeathProcessed = true;
            pProgress->DecreaseLife();
            m_pCurrentControlPlayer->SetState(CPlayer::PLAYER_STATE::ALIVE);

            if (pProgress->IsGameOver()) {
                CManager::GetFade()->SetFade(CScene::MODE::MODE_RESULT_GAMEOVER);
            }
            else {
                CManager::GetFade()->SetFade(CScene::MODE::MODE_GAME);
            }
        }
        
    }
    else
    {
        m_IsDeathProcessed = false;
    }

    
}

void CPlayerManager::Draw()
{
    if (m_pPlayer1) m_pPlayer1->Draw();
    if (m_pPlayer2) m_pPlayer2->Draw();;
}

//����L�����؂�ւ�
void CPlayerManager::SwitchPlayer()
{
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputGamepad* pJoypad = CManager::GetJoypad();

    //���삷�鎩�@�̐؂�ւ�
    if (!m_UseAbility == true)
    {
        if (pKeyboard->GetKeyboardTrigger(DIK_C) == true || pJoypad->GetJoypadTrigger(CInputGamepad::JOYKEY_LB) == true)
        {
            if (m_pCurrentControlPlayer == m_pPlayer1)
            {
                m_pPlayer1->SetAbilityActive(false);
                m_pCurrentControlPlayer = m_pPlayer2;
            }
            else
            {
                m_pPlayer2->SetAbilityActive(false);
                m_pCurrentControlPlayer = m_pPlayer1;
            }
        }
    }
}

//����
CPlayer* CPlayerManager::Create(TYPEPLAYER type, const D3DXVECTOR3& pos)
{
    CPlayer* pPlayer = nullptr;

    switch (type) {
    case TYPEPLAYER::PLAYER_1:
        m_pPlayer1 = CPlayer1::Create(pos);
        return m_pPlayer1;

    case TYPEPLAYER::PLAYER_2:
        m_pPlayer2 = CPlayer2::Create(pos);
        return m_pPlayer2;

    default:
        return nullptr;
    }
}

void CPlayerManager::CheckDeath(CPlayer* player) {
    if (player->GetPos().y < -50.0f) {
        player->SetState(player->PLAYER_STATE::DEAD);
    }
}
