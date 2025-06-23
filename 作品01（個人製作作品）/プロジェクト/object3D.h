//============================================================
//
//object3D.h
//
//============================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include "main.h"
#include "object.h"
#define NUM_POLYGON (15)

//3D�I�u�W�F�N�g�N���X
class CObject3D : public CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_3D;


	CObject3D();
	~CObject3D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex, D3DXVECTOR2 fTexpos);		//�e�N�X�`�����蓖��
	void SetParam(D3DXVECTOR3 length);
	void Setpos(D3DXVECTOR3 pos);
	static CObject3D* Create();
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��

	D3DXVECTOR3 m_pos3D;		//�ʒu
	D3DXVECTOR3 m_rot3D;		//�p�x
	D3DXMATRIX m_mtxWorld;

	
	float m_fLength3D_x;
	float m_fLength3D_y;
	float m_fLength3D_z;

	float m_NowTexpos_x;
	float m_NowTexpos_y;
};
#endif

