//============================================================
//
//player.h
//
//============================================================
#ifndef _CPlayer_H_
#define _CPlayer_H_
#include "main.h"
#include "objectX.h"
#include "goal.h"
#include "item.h"
#include "sound.h"
#define PARTS_FILE	"data\\motion.txt"
constexpr float  JUMP_INC(38.0f);
constexpr float  JUMP_INC_POWERUP(50.0f);
constexpr float  JUMP_INC_ITEMUSE(1.25f);
constexpr float  PLAYER_RADIUS(100.0f);
constexpr int POWERCOUNT = 1000;
constexpr int WARNINGLINE = 850;
constexpr int NUM_PATTERN = 50;
constexpr float MOVEDEC = 0.4f;
constexpr float DEAD_ZONE = 8000.0f;
constexpr float STICK_ZONE = 0.5f;
//3Dオブジェクトクラス
class CPlayer : public CObjectX
{
public:
	typedef enum //プレイヤーのモデル判定用タイプ
	{
		NONE = 0,
		PLAYER_1_N_NOM,
		PLAYER_2_S_NOM,
		PLAYER_1_N_MAG,
		PLAYER_2_S_MAG,
		PLAYER_MAX,
	}MESHPLAYER;

	enum PLAYER_STATE
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

	D3DXVECTOR3& GetPos() { return m_pos; }	//位置情報を取得
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	TYPEPLAYER GetPlayerType();				//プレイヤーの種類
	void SetPlayerType(TYPEPLAYER type);
	PLAYER_BLOCK_ST GetState_Block();		//触れているブロックの種類
	void SetState_Block(PLAYER_BLOCK_ST state_B);
	void SetAbilityActive(bool active) { m_IsAbilityActive = active; }
	bool IsAbilityActive() const { return m_IsAbilityActive; }
	virtual void ApplyMovementModifier() = 0;
	bool IsDead() const { return m_PlayerState == PLAYER_STATE::DEAD; }
	void SetState(PLAYER_STATE state) { m_PlayerState = state; }
	//重力操作
	void SetEnableGravity(bool enable) { m_bEnableGravity = enable; }
	bool IsGravityEnabled() const { return m_bEnableGravity; }
protected:
	static int m_Numplayer;					//自機の数
	LPDIRECT3DTEXTURE9 m_pTexture;
	static D3DXVECTOR3 m_PosOld;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_AveragePlayer_pos;
	TYPEPLAYER m_TypePlayer;	//プレイヤーのタイプ判定（1，2）
	PLAYER_BLOCK_ST m_PlayerState_Block;	//プレイヤーがどの種類ブロックに触れているか
	PLAYER_STATE m_PlayerState = ALIVE;
	static LPD3DXMESH m_pMesh_Player[PLAYER_MAX];
	static LPD3DXBUFFER m_pBuffMat_Player[PLAYER_MAX];
	static DWORD m_dwNumMat_Player[PLAYER_MAX];
	static D3DXMATERIAL* m_pMaterial_Player;
	static LPDIRECT3DTEXTURE9 m_pTexture_Player[NUM_TEXTURE];

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
	CSound* m_pSound_Player;
};


class CPlayer1 :public CPlayer
{
public:
	HRESULT Init() override;
	void Update() override;
	void Draw() override;
	void ApplyMovementModifier() override;
	static CPlayer1* Create(D3DXVECTOR3 pos);

};

class CPlayer2 :public CPlayer
{
public:
	HRESULT Init() override;
	void Update() override;
	void Draw() override;
	void ApplyMovementModifier() override;
	static CPlayer2* Create(D3DXVECTOR3 pos);

};
#endif
