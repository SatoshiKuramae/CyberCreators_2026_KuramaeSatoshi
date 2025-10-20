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

    if (m_pCurrentControlPlayer)
    {
        m_pCurrentControlPlayer->Playermove(); // 操作可能時のみ
    }

    //操作できる自機をわかりやすくするために色を変えました
    if (m_pCurrentControlPlayer == m_pPlayer1)
    {
        m_pPlayer1->SetColor(D3DXCOLOR(1, 1, 0, 1)); // 黄色：選択中
        m_pPlayer2->SetColor(D3DXCOLOR(1, 1, 1, 1)); // 白：非選択
    }
    else
    {
        m_pPlayer1->SetColor(D3DXCOLOR(1, 1, 1, 1));
        m_pPlayer2->SetColor(D3DXCOLOR(1, 1, 0, 1));
    }

    //アイテム使用中は色が変わる
    if (m_pCurrentControlPlayer->GetItemfrag() == true)
    {
        m_pCurrentControlPlayer->SetColor(D3DXCOLOR(1, 0, 0, 1));
    }

    if (pKeyboard->GetKeyboardPress(DIK_M) == true || pJoypad->GetJoypadPress(CInputGamepad::JOYKEY_RB) == true)
    {
        m_UseAbility = true;
        //ゲージ数値によって変化する
        if (Gauge > 0.0f)
        {
            //ゲージがあるとき
            pProgress->DecreaseAbilityGauge(0.5);
            if (m_pCurrentControlPlayer)
            {
                m_pCurrentControlPlayer->SetAbilityActive(true);
            }
        }
        else
        {
            //ゲージがなくなったら
            if (m_pCurrentControlPlayer)
            {
                m_pCurrentControlPlayer->SetAbilityActive(false);
            }
        }
    }
    else
    {
        m_UseAbility = false;
        pProgress->IncreaseAbilityGauge(1.0);
        if (m_pCurrentControlPlayer) 
        {
            m_pCurrentControlPlayer->SetAbilityActive(false);
        }
    }

    CPlayer* pActive = m_pCurrentControlPlayer;
    CPlayer* pInactive = (pActive == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

    if (pActive->IsAbilityActive()) 
    {
        // アビリティ発動中は非操作側の重力OFF
        pInactive->SetEnableGravity(false);
    }
    else 
    {
        // アビリティ未発動なら通常通り重力ON
        pInactive->SetEnableGravity(true);
    }

    // アビリティ発動中であれば非操作プレイヤーを引き付ける
    if (m_pCurrentControlPlayer && m_pCurrentControlPlayer->IsAbilityActive()) 
    {
        CPlayer* pInactive = (m_pCurrentControlPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

        if (pInactive)
        {
            D3DXVECTOR3 from = pInactive->GetPos();
            D3DXVECTOR3 to = m_pCurrentControlPlayer->GetPos();

            D3DXVECTOR3 direction = to - from;
            float dist = D3DXVec3Length(&direction);
            const float minDistance = 30.0f;   // この距離以下なら吸着完了とみなす
            const float pullSpeed = 10.0f;       // 安定吸着のために小さく設定

            // 一定距離以下なら引き寄せを止める
            if (dist < minDistance)
            {
                pInactive->SetMove(D3DXVECTOR3(0, 0, 0));  // 停止
                return;
            }

            // 吸着方向を正規化
            D3DXVec3Normalize(&direction, &direction);

            // 現在の移動量を取得し、吸着力を合成
            D3DXVECTOR3 currentMove = pInactive->GetMove();

            // 吸着速度は直接移動ではなく、徐々に合成
            currentMove.x += direction.x * pullSpeed;
            currentMove.y += direction.y * pullSpeed;

            // 移動量を制限
            const float maxSpeed = 20.0f;

            //自機同士がめり込まないように対策
            // X方向のクランプ
            if (currentMove.x > maxSpeed)
                currentMove.x = maxSpeed;
            else if (currentMove.x < -maxSpeed)
                currentMove.x = -maxSpeed;

            // Y方向のクランプ
            if (currentMove.y > maxSpeed)
                currentMove.y = maxSpeed;
            else if (currentMove.y < -maxSpeed)
                currentMove.y = -maxSpeed;


            pInactive->SetMove(currentMove);
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

            if (pProgress->IsGameOver()) 
            {
                CManager::GetFade()->SetFade(CScene::MODE::MODE_RESULT_GAMEOVER);
            }
            else 
            {
                CManager::GetFade()->SetFade(CScene::MODE::MODE_GAME);
            }
        }
    }
    else
    {
        m_IsDeathProcessed = false;
    }


}

//描画処理
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

    Init();

    switch (type) 
    {
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


//死亡確認
void CPlayerManager::CheckDeath(CPlayer* player) 
{
    if (player->GetPos().y < -PLAYER_DEATH) 
    {
        player->SetState(player->PLAYER_STATE::DEAD);
    }
}
