//============================================================
//
//playermanager.h
//Author Kuramaesatoshi
// 
//============================================================

#include "player.h"
#include <vector>
#include "GameProgress.h"
#pragma once

constexpr float PLAYER_DEATH(50.0f);

//�v���C���[�}�l�[�W���[�N���X
class CPlayerManager {
public:
    enum class TYPEPLAYER {
        PLAYER_1,
        PLAYER_2
        // ���ɂ��K�v�ɉ����Ēǉ��\
    };

    CPlayer* Create(TYPEPLAYER type, const D3DXVECTOR3& pos);
    void Init();
    void Update();
    void Draw();
    void Uninit();

    void SwitchPlayer(); // ����v���C���[�̐؂�ւ�
    
    CPlayer* GetPlayer1() const { return m_pPlayer1; }
    CPlayer* GetPlayer2() const { return m_pPlayer2; }

    void SetPlayer1(CPlayer* player) { m_pPlayer1 = player; }
    void SetPlayer2(CPlayer* player) { m_pPlayer2 = player; }
    void CheckDeath(CPlayer* player);


private:
    CPlayer* m_pPlayer1 = nullptr;
    CPlayer* m_pPlayer2 = nullptr;
    CPlayer* m_pCurrentControlPlayer = nullptr;
    bool m_IsDeathProcessed = false;        //���S�t���O�̔�����P�x�̂ݒʂ�悤�ɂ��邽�ߕK�v
    bool m_UseAbility = false;
    
};

