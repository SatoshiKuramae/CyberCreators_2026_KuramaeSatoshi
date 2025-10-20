//============================================================
//
//player.h
//Author Kuramaesatoshi
//============================================================

#ifndef _CPlayer_H_
#define _CPlayer_H_
#include "main.h"
#include "objectX.h"
#include "goal.h"
#include "item.h"
#include "sound.h"
#include "block.h"
#include "collision.h"

#define PARTS_FILE	"data\\motion.txt"
constexpr float  JUMP_INC(35.0f);
constexpr float  JUMP_INC_POWERUP(50.0f);
constexpr float  JUMP_INC_ITEMUSE(1.25f);
constexpr float  PLAYER_RADIUS(100.0f);
constexpr int POWERCOUNT = 1000;
constexpr int WARNINGLINE = 850;
constexpr int NUM_PATTERN = 50;
constexpr float MOVEDEC = 0.4f;
constexpr float DEAD_ZONE = 8000.0f;
constexpr float STICK_ZONE = 0.5f;
constexpr float PLAYERCOLL(40.0f);
constexpr float BLOCKCOLLISION_X(BLOCK_X - 5.0f);
constexpr float BLOCKCOLLISION_Y(BLOCK_X - 5.0f);
constexpr float RESETPOS((BLOCK_X + PLAYERCOLL) + 0.1f);

//プレイヤークラス
class CPlayer : public CObjectX
{
public:
	typedef enum //プレイヤーのモデル判定用
	{
		NONE = 0,
		PLAYER_1_N_NOM,
		PLAYER_2_S_NOM,
		PLAYER_1_N_MAG,
		PLAYER_2_S_MAG,
		PLAYER_MAX,
	}MESHPLAYER;

	enum PLAYER_STATE	//プレイヤーの状態
	{
		ALIVE,
		DEAD,
		RESPAWNING
	};
	enum TYPEPLAYER { PLAYER_1, PLAYER_2 };

	//プレイヤーが触れている物の種類
	typedef enum
	{
		STATE_NOMALBLOCK = 0,
		STATE_N_BLOCK,
		STATE_S_BLOCK,
		STATE_MOVEBLOCK_R,
		STATE_MOVEBLOCK_L,
	}PLAYER_BLOCK_ST;

	typedef enum
	{
		C_Player_1,
		C_Player_2,
	}ControlPlayer;

	CPlayer();
	virtual ~CPlayer();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void Playermove();
	virtual void UpdateJump();
	static HRESULT Load();
	static void Unload();

	D3DXVECTOR3 Collision(D3DXVECTOR3 pos);

	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報を取得
	D3DXVECTOR3& GetMove() { return m_move; }
	D3DXVECTOR3 GetSize() const{ return m_Size; }
	bool GetItemfrag() const { return m_Itemflag; }

	TYPEPLAYER GetPlayerType();				//プレイヤーの種類
	void SetPlayerType(TYPEPLAYER type);
	PLAYER_BLOCK_ST GetState_Block();		//触れているブロックの種類
	void SetState_Block(PLAYER_BLOCK_ST state_B);
	void SetAbilityActive(bool active) { m_IsAbilityActive = active; }
	bool IsAbilityActive() const { return m_IsAbilityActive; }
	virtual void AbirityMoveflag() = 0;
	bool IsDead() const { return m_PlayerState == PLAYER_STATE::DEAD; }
	void SetState(PLAYER_STATE state) { m_PlayerState = state; }
	//重力操作
	void SetEnableGravity(bool enable) { m_bEnableGravity = enable; }
	bool IsGravityEnabled() const { return m_bEnableGravity; }

	//色変更
	void SetColor(D3DXCOLOR color) { m_color = color; }
	D3DXCOLOR GetColor() const { return m_color; }
protected:

	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_PosOld= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	
	D3DXVECTOR3 m_AveragePlayer_pos;	//自機二人の中心点
	TYPEPLAYER m_TypePlayer;	//プレイヤーのタイプ判定（1，2）
	PLAYER_BLOCK_ST m_PlayerState_Block;	//プレイヤーがどの種類ブロックに触れているか
	PLAYER_STATE m_PlayerState = ALIVE;		//現在の自機のステート

	D3DXMATRIX m_mtxWorld;
	static LPD3DXMESH m_pMesh_Player[PLAYER_MAX];
	static LPD3DXBUFFER m_pBuffMat_Player[PLAYER_MAX];
	static DWORD m_dwNumMat_Player[PLAYER_MAX];
	static D3DXMATERIAL* m_pMaterial_Player;
	static LPDIRECT3DTEXTURE9 m_pTexture_Player[NUM_TEXTURE];
	D3DXCOLOR m_color = D3DXCOLOR(1, 1, 1, 1);

	int m_ControlPlayer;
	bool m_bDeath;
	bool m_Goalflag;
	bool m_Itemflag;
	bool m_Jump;
	bool m_IsAbilityActive = false;
	bool m_bEnableGravity = true;
	int m_PowerupCnt;
	int m_MagCnt;
	float m_jumpPower;  // デフォルトジャンプ力

private:

	D3DXVECTOR3 m_Size = { PLAYERCOLL, PLAYERCOLL, PLAYERCOLL };
	
	CSound* m_pSound_Player;
};

//プレイヤー1クラス
class CPlayer1 :public CPlayer
{
public:
	HRESULT Init() override;
	void Update() override;
	void Draw() override;
	void AbirityMoveflag() override;
	static CPlayer1* Create(D3DXVECTOR3 pos);

};

//プレイヤー2クラス
class CPlayer2 :public CPlayer
{
public:
	HRESULT Init() override;
	void Update() override;
	void Draw() override;
	void AbirityMoveflag() override;
	static CPlayer2* Create(D3DXVECTOR3 pos);

};
#endif
