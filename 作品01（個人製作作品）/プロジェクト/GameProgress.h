//============================================================
//
//Gameprogress.h
//Author Kuramaesatoshi
//============================================================
#pragma once

//�Q�[���̐i�s��񂾂��ʃN���X��
class CGameprogress {
public:
    CGameprogress();
    ~CGameprogress();
    void Reset();                            // �c�@�Ȃǂ̏�����
    void DecreaseLife();       // �c�@��1���炷
    int  GetLife() const;                // ���݂̎c�@��
    void SetLife(int life);               // �����I�ɐݒ�
    bool IsGameOver() const { return m_Life <= 0; }         // �Q�[���I�[�o�[����

    void IncreaseAbilityGauge(float amount); // �񕜁i�������Ƃ��j
    void DecreaseAbilityGauge(float amount); // ����i�������j
    void SetAbilityGauge(float value);
    float GetAbilityGauge() const;

    static const int MAX_ABILITY_GAUGE = 100;
private:
    int m_Life = 3;
    
    float m_nAbilityGauge = MAX_ABILITY_GAUGE;

};
