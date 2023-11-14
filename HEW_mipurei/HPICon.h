#pragma once
#include "AnimationHitObject.h"

/*
����ҁF����r��
�v���C���[�N���X�Ɏ�������O��̃A�C�R����HP�̃N���X�ł��B
*/

class HPICon :
	public AnimationHitObject
{
	enum IconState{
		State_Recvery,
		State_Decrese,
		State_None
	};


public:
	HPICon(int _MaxHP);
	HPICon(int _MaxHP,float _x,float _y);
	~HPICon();
	void Update(int _HP);
	void Draw();
private:
	int NowHP;
	int OldHP;
	int HPIndex;
	int MaxHP;
	bool HPDecreseFlg;//HP�����t���O
	bool HPRecoverFlg;//HP�񕜃t���O
	bool DecresePlayFlg;
	bool RecoverPlayFlg;

	int FrameWait=0;
	int DecreFrameWait = 0;

	IconState * mpIconState;

	bool Recovery(AnimationHitObject * _obj);
	bool Decrease(AnimationHitObject * _obj);

	AnimationHitObject* DrawObj;
};
