//============================================================
//
//object.h
//Author Kuramaesatoshi
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

	CObject(int nPriority = 3);		//描画優先設定
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static CObject* GetObject(int nIdx,int nPri);
	TYPE GetType();
	void SetType(TYPE type);
	static void ReleaseAll();	//全オブジェクトの解放
	static void UpdateAll();	//全オブジェクトの更新
	static void DrawAll();		//全オブジェクトの描画

protected:
	void Release();				//自分自身の解放
private:
	static CObject* m_apObject[MAX_PRIORITY][NUMOBJECT];	//Priority最大数とオブジェクト最大数
	static int m_nNumAll;					//オブジェクト総数
	int m_nID;								//自分自身のID
	int m_nPriority;						//描画優先度
	TYPE m_type;							//オブジェクトタイプ

	//オブジェクト管理
	static CObject* m_pTop;	//先頭のオブジェクトのポインタ
	static CObject* m_pCur;	//現在（最後尾）のポインタ
	CObject* m_Prev;		//前のオブジェクトのポインタ
	CObject* m_pNext;		//次のオブジェクトのポインタ
	bool m_bDeath;			//死亡フラグ
	static bool m_bPause;			//ポーズフラグ
};
#endif