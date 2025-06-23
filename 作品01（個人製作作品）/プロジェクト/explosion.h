//=======================================================
//
//explosion.h
//
//Author Kuramaesatoshi
//=======================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D.h"

#define MAX_EXPLOSION (500)		//�����̍ő吔
#define EXPLOSION_TX_X (0.125f)
//�����G�t�F�N�g�\����
class CExplosion : public CObject2D
{
public:
	//�����\���̂̒�`
	typedef struct
	{
		int nCounterAnim;	//�A�j���[�V�����J�E���^�[
		int nPatternAnim;	//�A�j���[�V�����p�^�[��No.
	}Explosion;

	CExplosion();
	~CExplosion();
	HRESULT Init();
	void Uninit();
	void Draw();
	void Update();
	static CExplosion* Create(D3DXVECTOR3 pos);
	static HRESULT Load();	//�e�N�X�`���̃��[�h
	static void Unload();

private:
	static LPDIRECT3DTEXTURE9 m_pTextureExplosion;

};
#endif
