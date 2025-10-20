//===============================================================================
//
//resultrank.h
//Author Kuramaesatoshi
//===============================================================================
#ifndef _RESULTRANK_H_
#define _RESULTRANK_H_
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "texture.h"

constexpr int RANK_DIFF = 10;
constexpr float RANKUI_PARAM = 400.0f;

//テクスチャ管理
class CResultrank : public CObject2D
{
public:

	CResultrank(int nPriority = 11);
	~CResultrank() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CResultrank* Create(D3DXVECTOR3 pos);

private:
	static int m_nTextureResult;
	int m_Selectstage;
	int m_Besttime;
	int m_PlayerTime;
};
#endif

