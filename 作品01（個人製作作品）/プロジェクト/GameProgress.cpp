//=======================================================
//
//�Q�[�����̃f�[�^�i���C�t��Q�[�W�֌W�j
//
//=======================================================
#include "GameProgress.h"


//�R���X�g���N�^
CGameprogress::CGameprogress() 
{
	/* ���������� */ 
	m_Life = 3;
	m_nAbilityGauge = 100;
}
//�f�X�g���N�^
CGameprogress::~CGameprogress() 
{

}

//���Z�b�g
void CGameprogress::Reset() 
{ 
	m_Life = 3; 
	m_nAbilityGauge = 100;
}

//�c�@���炷
void CGameprogress::DecreaseLife() 
{
	if (m_Life > 0)
	{
		m_Life -= 1;
	}
}

//���̎c�@���擾
int CGameprogress::GetLife() const 
{
	return m_Life; 
}

//�Z�b�^�[
void CGameprogress::SetLife(int life) 
{
	m_Life = life; 
}

//�Q�[�W�𑝂₷
void CGameprogress::IncreaseAbilityGauge(float amount) {
	m_nAbilityGauge += amount;
	if (m_nAbilityGauge > MAX_ABILITY_GAUGE) m_nAbilityGauge = MAX_ABILITY_GAUGE;
}

//�Q�[�W�����炷
void CGameprogress::DecreaseAbilityGauge(float amount) {
	m_nAbilityGauge -= amount;
	if (m_nAbilityGauge < 0) m_nAbilityGauge = 0;
}

//�Q�[�W�p�Z�b�^�[
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

//�Q�[�W�p���l�擾�p
float CGameprogress::GetAbilityGauge() const {
	return m_nAbilityGauge;
}