//============================================================
//
//bg.h
//
//Author Kuramaesatoshi
//============================================================
#ifndef _CBG_H_
#define _CBG_H_
#include "main.h"
#include "object2D.h"
#define TEX_X_PLAYER (0.25f)
#define PLYAYER_SP (10.0f)
//2D�I�u�W�F�N�g�N���X
class CBg : public CObject2D
{
public:

	CBg(int nPriority = 9);
	~CBg() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CBg* Create(D3DXVECTOR3 pos);
	static HRESULT Load();	//�e�N�X�`���̃��[�h
	static void Unload();
private:
	static int m_pTextureBg;		//�e�N�X�`��
	
};
#endif


