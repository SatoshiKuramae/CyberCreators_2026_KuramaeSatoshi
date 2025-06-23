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

//2Dオブジェクトクラス
class CObject2D : public CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	//頂点情報
		float rhw;			//座標変換用係数
		D3DCOLOR col;		//頂点カラー
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	CObject2D(int nPriority = 1);
	~CObject2D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CObject2D* Create();
	void BindTexture(LPDIRECT3DTEXTURE9 pTex,D3DXVECTOR2 fTexpos);		//テクスチャ割り当て
	D3DXVECTOR3& GetPos() { return m_posPolygon; }	//位置情報などを取得
	void Setpos(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//移動量の設定
	D3DXVECTOR3& GetMove() { return  m_move; }			//移動量の取得
	void SetParam(float wide, float height);
	void SetAnim(float m_Texpos_x_MIN, float m_Texpos_x_MAX);
	void SetLengthPolygon(float length);
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ

	D3DXVECTOR3 m_posPolygon;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rotPolygon;		//角度

	float m_fAnglePolygon;			//対角線の角度
	float m_fLengthPolygon;			//対角線の長さ
	D3DXVECTOR2 m_texcnt;
	VERTEX_2D* m_pVtx;
	float m_MAXTexpos_x;
	float m_MINTexpos_x;
	float m_NowTexpos_x;
	float m_NowTexpos_y;
	float m_fGaugeRate = 1.0f; // 1.0f = 100%
	
};
#endif
