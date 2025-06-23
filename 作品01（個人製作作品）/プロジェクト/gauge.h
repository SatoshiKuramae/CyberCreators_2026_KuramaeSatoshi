#include "object2D.h"
#pragma once

//ゲージクラス
class CGauge :public CObject2D
{
public:
	CGauge(int nPriority = 12);
	~CGauge();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetRate(float rate);
	static CGauge* Create(D3DXVECTOR3 pos);
private:
	int m_pTextureGauge;
};

