//===============================================================================
//
//number.cpp
//Author Kuramaesatoshi
//===============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object.h"
#include "object2D.h"
#include <iostream>
#include <string>
#include "texture.h"

//テクスチャ管理
class CNumber : public CObject2D
{
public:
	
	CNumber(int nPriority = 10);
	~CNumber() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Setnumber(float m_Texpos_MIN, float m_Texpos_MAX);

private:
	float m_Texpos_MIN;
	float m_Texpos_MAX;
	int m_nTexture;
};
#endif
