//============================================================
//
//objectX.h
//Author Kuramaesatoshi
//============================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_
#include "main.h"
#include "object.h"
#define NUM_TEXTURE (50)

//3D�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:
	
	CObjectX();
	~CObjectX() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Load();
	void Setpos(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);//�ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot);
	void SetScale(D3DXVECTOR3 scale);
	void BindMesh(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat, D3DXMATERIAL* pMat, LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3& GetRot() { return m_rot; }

		// CObject �̏������z�֐�������
	D3DXVECTOR3 GetPos() const override { return m_pos; }
	D3DXVECTOR3 GetSize() const override { return m_size; }
	TYPE GetType() const override { return m_type; }

	// ���f���n�̋��ʏ�����������
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }

	//�F�ύX
	void SetColor(D3DXCOLOR color)
	{
		m_diffuseColor = color;
	}
	
protected:
	
	D3DXVECTOR3 m_size;
	TYPE m_type = TYPE::NONE;
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXVECTOR3 m_scale;	//�g�嗦
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXMATRIX m_mtxWorld;
	D3DXCOLOR m_diffuseColor = D3DXCOLOR(1, 1, 1, 1);

	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXMATERIAL* m_pMaterial;
	LPDIRECT3DTEXTURE9 m_pTexture[NUM_TEXTURE];
};
#endif


