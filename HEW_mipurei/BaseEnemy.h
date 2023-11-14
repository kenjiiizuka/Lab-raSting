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
	virtual bool GetDeath();                                    //! ���ꂽ�Ƃ��Ɉ�x�������ꂽ���Ƃ�Ԃ��֐�
	TailReaction Reaction;
	void SetHitPlayer(bool _hit);                              //! �v���C��[�ɓ����������ǂ���
	virtual TailReaction SetStingPower(float _Power, bool _Elect);
protected:
	Player * mcPlayer;
	bool ChaseFlg;	//! �G��ǂ������Ă��邩�ǂ����̔��f
	bool Stinged; //! �h���ꂽ�t���O
	bool Death;
	bool Deathed;
	bool HitPlayer; //! �v���C���[�ɓ����������Ƃ𔻒f����t���O
	bool Elect;
private:	
	int Count;
	float Power;
	float Speed;
	HitStop * mcpHitStop;
};
