#pragma once
#include "Character.h"
class HitStop
{
public:
	HitStop(Character * _HitAnimSprite);	//! �R���X�g���N�^
	~HitStop();								//! �f�X�g���N�^
	int HitStopStart(int _HitMax);
	bool HitStoptime();	//! �q�b�g�X�g�b�v�֐�
	bool HitStopFlg;	//! �X�g�b�v�������f
	bool HitJudge;		//! �q�b�g�X�g�b�v�̍��W���Ƃ邩�ǂ���
	Vector2 stoppos;	//! �q�b�g�X�g�b�v�̍��W
	//! �q�b�g�X�g�b�v���邩�ǂ����@
	bool GetHitJugde();
private:
	int HitCount;
	int HitMax;
	Character* mcpHitStopAnimation;
};

