//===============================================================================
//
// 数字
// 
//===============================================================================

#include "number.h"
#include "manager.h"
#include "texture.h"
#include "object.h"
//コンストラクタ
CNumber::CNumber(int nPriority) :CObject2D(nPriority)
{
	m_Texpos_MIN = 0;
	m_Texpos_MAX = 0;
}
// デストラクタ
CNumber::~CNumber()
{

}


HRESULT CNumber::Init()
{
	CTexture* pTex = CManager::GetTexture();

	m_nTexture = pTex->Regist("data\\texture\\timer_tex.png");

	CObject2D::BindTexture(pTex->GetAddress(m_nTexture), D3DXVECTOR2(10, 1));
	CObject2D::Init();
	return S_OK;
}

void CNumber::Uninit()
{
	CObject2D::Uninit();
}

void CNumber::Draw()
{
	CObject2D::Draw();
}

void CNumber::Update()
{
	CObject2D::Update();
}

CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CNumber* pNumber = new CNumber;
	pNumber->Setpos(pos);
	pNumber->SetParam(size.x, size.y);
	pNumber->Init();
	pNumber->SetType(CObject::TYPE::NUMBER);
	return pNumber;
}

void CNumber::Setnumber(float m_Texpos_MIN, float m_Texpos_MAX)
{
	CObject2D::SetAnim(m_Texpos_MIN, m_Texpos_MAX);
}