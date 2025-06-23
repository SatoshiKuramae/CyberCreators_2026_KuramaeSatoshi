//============================================================
//
//gaugeframe.h
//Author Kuramaesatoshi
//============================================================
#include "object2D.h"
#pragma once

//ゲージクラス
class CGaugeframe :public CObject2D
{
public:
	CGaugeframe(int nPriority = 13);
	~CGaugeframe();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CGaugeframe* Create(D3DXVECTOR3 pos);
private:
	int m_pTextureGaugeframe;
};