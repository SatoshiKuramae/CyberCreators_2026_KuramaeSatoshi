#include "player.h"
#include <vector>
#include "GameProgress.h"
#pragma once
class CPlayerManager {
public:
    enum class TYPEPLAYER {
        PLAYER_1,
        PLAYER_2
        // 他にも必要に応じて追加可能
    };
    CPlayer* Create(TYPEPLAYER type, const D3DXVECTOR3& pos);
    void Init();
    void Update();
    void Draw();
    void Uninit();

    void SwitchPlayer(); // 操作プレイヤーの切り替え
    CPlayer* GetCurrentPlayer();
    CPlayer* GetPlayer1() const { return m_pPlayer1; }
    CPlayer* GetPlayer2() const { return m_pPlayer2; }
    void SetPlayer1(CPlayer* player) { m_pPlayer1 = player; }
    void SetPlayer2(CPlayer* player) { m_pPlayer2 = player; }
    void CheckDeath(CPlayer* player);
    //void OnPlayerDeath();  // 残機処理
    //int GetLife() const;

private:
    CPlayer* m_pPlayer1 = nullptr;
    CPlayer* m_pPlayer2 = nullptr;
    CPlayer* m_pCurrentControlPlayer = nullptr;
    bool m_IsDeathProcessed = false;        //死亡フラグの判定を１度のみ通るようにするため必要
    bool m_UseAbility = false;
    
};

