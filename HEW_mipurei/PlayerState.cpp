#include "PlayerState.h"

//! �v���C���[�X�e�[�^�X�̃R���X�g���N�^
//! Player�N���X�ŃR���X�g���N�^�Ŋe�l�����炷���߂ɂ����Œl��ݒ�
PlayerStatus::PlayerStatus()
{
	MoveSpeed = 0.008f;
	InitJumpPower = 0.03f;
	TmpJumpPower = 0;
	HP = 3;
	MoveAble = true;
}

//! �v���C���[�̃W�����v�Ŏg���\���̂̃R���X�g���N�^
SJump::SJump()
{
	FrameCnt = 0;
	AnimCnt = 0;
	Jump = false;
	Doing = false;
	End = false;
	Up = false;
}

//! �v���C���[�̃_���[�W�Ɋւ���\����
SDamage::SDamage()
{
	Cnt = 0;
	Flg = false;
	Effect = false;
	NockBack = false;
	NockBackWay = Left;
}

SElectricity::SElectricity()
{
	ChargeCnt = 0;
	SuperCnt = 0;
	EndSuper = false;
	UpRate = 1.0f;
	Super = false;
}
