#pragma once
#include "Character.h"
#include "HitStop.h"
#include "PlayerState.h"
#include "Player.h"

class BaseEnemy :
	public Character
{
protected:

	typedef struct
	{
		bool LiveFlg;
		float MoveDis;
		bool MoveDirFlg;
		bool CarryMeFlg;
	} EnemyStatus;
	EnemyStatus Status;
public:
	BaseEnemy();
	BaseEnemy(float _x, float _y);
	~BaseEnemy();

	void Update() override;
	void Draw() override;
	float SetMove(float _Speed);
	void SetCarryFlg(bool _Carryme);
	void SetMoveVec(Vector2 _MoveVec);
	void SetPlayer(Player * _Player);
	void Move();
	virtual void Destroy();
	virtual bool GetDeath();                                    //! やられたときに一度だけやられたことを返す関数
	TailReaction Reaction;
	void SetHitPlayer(bool _hit);                              //! プレイやーに当たったかどうか
	virtual TailReaction SetStingPower(float _Power, bool _Elect);
protected:
	Player * mcPlayer;
	bool ChaseFlg;	//! 敵を追いかけているかどうかの判断
	bool Stinged; //! 刺されたフラグ
	bool Death;
	bool Deathed;
	bool HitPlayer; //! プレイヤーに当たったことを判断するフラグ
	bool Elect;
private:	
	int Count;
	float Power;
	float Speed;
	HitStop * mcpHitStop;
};
