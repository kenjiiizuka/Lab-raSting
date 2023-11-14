#pragma once
#include "ReNecthor.h"

//! 1-5 用のネクトール
class LeapDebri;

class Necthor1_5 :
	public ReNecthor
{
public:
	Necthor1_5();
	Necthor1_5(float _x, float _y);
	~Necthor1_5();

	void Update();
	void Draw();
	void CollisionUpdate();

private:
	void Idol();
	void Atk_PressHammer();
	void Atk_ShockWave();
	void Atk_RushWave();
	void Atk_LeapDebri();
	void AttackStateMachine();
	void SmokeUpdate();
	LeapDebri * mcpLeapdebri[3];

	int RandamCnt = 0; //! 戦闘開始から数えるこの数値をつかってランダム行動ときは決める
	int LeapDebriPreparation = 0; //! がれきが飛び出てくる攻撃の予備動作
	int LeapDebriAtkCnt;          //! がれきが飛び出てくる攻撃を何回したか
	bool RushWaveAttack = false;
};

