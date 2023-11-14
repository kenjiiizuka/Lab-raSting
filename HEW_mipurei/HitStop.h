#pragma once
#include "Character.h"
class HitStop
{
public:
	HitStop(Character * _HitAnimSprite);	//! コンストラクタ
	~HitStop();								//! デストラクタ
	int HitStopStart(int _HitMax);
	bool HitStoptime();	//! ヒットストップ関数
	bool HitStopFlg;	//! ストップ中か判断
	bool HitJudge;		//! ヒットストップの座標をとるかどうか
	Vector2 stoppos;	//! ヒットストップの座標
	//! ヒットストップするかどうか　
	bool GetHitJugde();
private:
	int HitCount;
	int HitMax;
	Character* mcpHitStopAnimation;
};

