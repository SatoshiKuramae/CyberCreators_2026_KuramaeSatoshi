//============================================================
//
//object.h
//
//============================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"


class CObject
{
public:
	typedef enum
	{
		NONE=0,
		ENEMY,
		PLAYER,
		PLAYER01,
		PLAYER02,
		BULLET,
		BLOCK,
		FLOOR,
		ITEM,
		GOAL,
		NUMBER,
		EFFECT,
	}TYPE;

	CObject(int nPriority = 3);		//�`��D��ݒ�
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static CObject* GetObject(int nIdx,int nPri);
	TYPE GetType();
	void SetType(TYPE type);
	static void ReleaseAll();	//�S�I�u�W�F�N�g�̉��
	static void UpdateAll();	//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();		//�S�I�u�W�F�N�g�̕`��

protected:
	void Release();				//�������g�̉��
private:
	static CObject* m_apObject[MAX_PRIORITY][NUMOBJECT];	//Priority�ő吔�ƃI�u�W�F�N�g�ő吔
	static int m_nNumAll;					//�I�u�W�F�N�g����
	int m_nID;								//�������g��ID
	int m_nPriority;						//�`��D��x
	TYPE m_type;							//�I�u�W�F�N�g�^�C�v

	//�I�u�W�F�N�g�Ǘ�
	static CObject* m_pTop;	//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur;	//���݁i�Ō���j�̃|�C���^
	CObject* m_Prev;		//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;		//���̃I�u�W�F�N�g�̃|�C���^
	bool m_bDeath;			//���S�t���O
	static bool m_bPause;			//�|�[�Y�t���O
};
#endif