//=======================================================
//
//ゲーム中のデータ（ライフやゲージ関係）
//
//=======================================================
#include "GameProgress.h"


//コンストラクタ
CGameprogress::CGameprogress() 
{
	/* 初期化処理 */ 
	m_Life = 3;
	m_nAbilityGauge = 100;
}
//デストラクタ
CGameprogress::~CGameprogress() 
{

}

//リセット
void CGameprogress::Reset() 
{ 
	m_Life = 3; 
	m_nAbilityGauge = 100;
}

//残機減らす
void CGameprogress::DecreaseLife() 
{
	if (m_Life > 0)
	{
		m_Life -= 1;
	}
}

//今の残機を取得
int CGameprogress::GetLife() const 
{
	return m_Life; 
}

//セッター
void CGameprogress::SetLife(int life) 
{
	m_Life = life; 
}

//ゲージを増やす
void CGameprogress::IncreaseAbilityGauge(float amount) {
	m_nAbilityGauge += amount;
	if (m_nAbilityGauge > MAX_ABILITY_GAUGE) m_nAbilityGauge = MAX_ABILITY_GAUGE;
}

//ゲージを減らす
void CGameprogress::DecreaseAbilityGauge(float amount) {
	m_nAbilityGauge -= amount;
	if (m_nAbilityGauge < 0) m_nAbilityGauge = 0;
}

//ゲージ用セッター
void CGameprogress::SetAbilityGauge(float value) {
	if (value < 0) {
		m_nAbilityGauge = 0;
	}
	else if (value > MAX_ABILITY_GAUGE) {
		m_nAbilityGauge = MAX_ABILITY_GAUGE;
	}
	else {
		m_nAbilityGauge = value;
	}
}

//ゲージ用数値取得用
float CGameprogress::GetAbilityGauge() const {
	return m_nAbilityGauge;
}