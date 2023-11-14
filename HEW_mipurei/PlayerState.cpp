#include "PlayerState.h"

//! プレイヤーステータスのコンストラクタ
//! Playerクラスでコンストラクタで各値を減らすためにここで値を設定
PlayerStatus::PlayerStatus()
{
	MoveSpeed = 0.008f;
	InitJumpPower = 0.03f;
	TmpJumpPower = 0;
	HP = 3;
	MoveAble = true;
}

//! プレイヤーのジャンプで使う構造体のコンストラクタ
SJump::SJump()
{
	FrameCnt = 0;
	AnimCnt = 0;
	Jump = false;
	Doing = false;
	End = false;
	Up = false;
}

//! プレイヤーのダメージに関する構造体
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
