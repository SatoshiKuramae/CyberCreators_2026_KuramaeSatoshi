//============================================================
//
//object2D.h
//Author Kuramaesatoshi
//============================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "main.h"
#include "object.h"
#define TEX_X (0.1f)

//2D�I�u�W�F�N�g�N���X
class CObject2D : public CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	//���_���
		float rhw;			//���W�ϊ��p�W��
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	CObject2D(int nPriority = 1);
	~CObject2D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CObject2D* Create();
	void BindTexture(LPDIRECT3DTEXTURE9 pTex,D3DXVECTOR2 fTexpos);		//�e�N�X�`�����蓖��
	void Setpos(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3& GetMove() { return  m_move; }			//�ړ��ʂ̎擾
	void SetParam(float wide, float height);
	void SetAnim(float m_Texpos_x_MIN, float m_Texpos_x_MAX);
	void SetLengthPolygon(float length);

	// CObject �̏������z�֐�������
	D3DXVECTOR3 GetPos() const override { return m_pos; }
	D3DXVECTOR3 GetSize() const override { return m_size; }
	TYPE GetType() const override { return m_type; }

	// ���f���n�̋��ʏ�����������
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��

	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rotPolygon;		//�p�x

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	TYPE m_type = TYPE::NONE;

	float m_fAnglePolygon;			//�Ίp���̊p�x
	float m_fLengthPolygon;			//�Ίp���̒���
	D3DXVECTOR2 m_texcnt;
	VERTEX_2D* m_pVtx;
	float m_MAXTexpos_x;
	float m_MINTexpos_x;
	float m_NowTexpos_x;
	float m_NowTexpos_y;
	float m_fGaugeRate = 1.0f; // 1.0f = 100%
	
};
#endif
