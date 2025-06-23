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

//初期化処理
void CPlayerManager::Init()
{
	m_pCurrentControlPlayer = m_pPlayer1;

}

//終了処理
void CPlayerManager::Uninit()
{
    if (m_pPlayer1)m_pPlayer1->Uninit();
    if (m_pPlayer2)m_pPlayer2->Uninit();
}

//更新処理
void CPlayerManager::Update()
{
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputGamepad* pJoypad = CManager::GetJoypad();
    CGameprogress* pProgress = CManager::GetGameProgress();
    float Gauge = pProgress->GetAbilityGauge();
    SwitchPlayer();

    if (m_pCurrentControlPlayer) {
        m_pCurrentControlPlayer->Playermove(); // 操作可能時のみ
    }
    if (pKeyboard->GetKeyboardPress(DIK_M) == true || pJoypad->GetJoypadPress(CInputGamepad::JOYKEY_RB) == true)
    {
        m_UseAbility = true;
        //ゲージ数値によって変化する
        if (Gauge > 0.0f)
        {
            //ゲージがあるとき
            pProgress->DecreaseAbilityGauge(0.5);
            if (m_pCurrentControlPlayer) {
                m_pCurrentControlPlayer->SetAbilityActive(true);
            }
        }
        else
        {
            //ゲージがなくなったら
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
        // アビリティ発動中は非操作側の重力OFF
        pInactive->SetEnableGravity(false);
    }
    else {
        // アビリティ未発動なら通常通り重力ON
        pInactive->SetEnableGravity(true);
    }

    

    // アビリティ発動中であれば非操作プレイヤーを引き付ける
    if (m_pCurrentControlPlayer && m_pCurrentControlPlayer->IsAbilityActive()) {
        CPlayer* pInactive = (m_pCurrentControlPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

        if (pInactive) {

            D3DXVECTOR3 from = pInactive->GetPos();
            D3DXVECTOR3 to = m_pCurrentControlPlayer->GetPos();

            D3DXVECTOR3 direction = to - from;
            float pullSpeed_X = 10.0f;  // 吸着速度は低めで安定しやすくなる
            float pullSpeed_Y = 10.0f;

            // プレイヤー同士が近づきすぎないよう安全距離を設ける（重要）
            float dist = D3DXVec3Length(&direction);
            if (dist < PLAYER_RADIUS) {
                pInactive->SetMove(D3DXVECTOR3(0, 0, 0));  // 吸着完了
                return;
            }

            D3DXVec3Normalize(&direction, &direction);
            D3DXVECTOR3 pullMove = direction * 25.0f;  // 吸着速度

            // 吸着による移動を move にセット
            pInactive->SetMove(pullMove);
        }
    }


    CheckDeath(m_pPlayer1);
    CheckDeath(m_pPlayer2);

    //プレイヤーの死亡フラグを検知
    if (m_pCurrentControlPlayer && m_pPlayer1->IsDead() == true|| m_pPlayer2->IsDead()==true)
    {
        //マネージャー側では１度のみ通るように
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

//操作キャラ切り替え
void CPlayerManager::SwitchPlayer()
{
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    CInputGamepad* pJoypad = CManager::GetJoypad();

    //操作する自機の切り替え
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

//生成
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
