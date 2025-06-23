//============================================================
//
//Gameprogress.h
//Author Kuramaesatoshi
//============================================================
#pragma once

//ゲームの進行情報だけ別クラス化
class CGameprogress {
public:
    CGameprogress();
    ~CGameprogress();
    void Reset();                            // 残機などの初期化
    void DecreaseLife();       // 残機を1つ減らす
    int  GetLife() const;                // 現在の残機数
    void SetLife(int life);               // 強制的に設定
    bool IsGameOver() const { return m_Life <= 0; }         // ゲームオーバー判定

    void IncreaseAbilityGauge(float amount); // 回復（離したとき）
    void DecreaseAbilityGauge(float amount); // 消費（発動中）
    void SetAbilityGauge(float value);
    float GetAbilityGauge() const;

    static const int MAX_ABILITY_GAUGE = 100;
private:
    int m_Life = 3;
    
    float m_nAbilityGauge = MAX_ABILITY_GAUGE;

};
