#pragma once
#include "ReNecthor.h"

//! 1-5 �p�̃l�N�g�[��
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

	int RandamCnt = 0; //! �퓬�J�n���琔���邱�̐��l�������ă����_���s���Ƃ��͌��߂�
	int LeapDebriPreparation = 0; //! ���ꂫ����яo�Ă���U���̗\������
	int LeapDebriAtkCnt;          //! ���ꂫ����яo�Ă���U�������񂵂���
	bool RushWaveAttack = false;
};

