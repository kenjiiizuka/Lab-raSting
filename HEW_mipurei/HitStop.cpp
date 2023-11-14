#include "HitStop.h"
#include "FrameRateCalculator.h"
#include "AnimationHitObject.h"


HitStop::HitStop(Character * _mcpHitAnimSprite)
{
	mcpHitStopAnimation = _mcpHitAnimSprite;
	HitStopFlg = false;	//! ヒットストップを行うか判断　※条件は偽からスタート 
	HitJudge = false;	//! 座標をとるか判断　※条件は偽からスタート
	HitCount = 0;		//! カウントの初期化
}

HitStop::~HitStop()
{

}

int HitStop::HitStopStart(int _HitMax)
{

	HitStopFlg = true;	//! ヒットストップフラグ　オン

	HitMax = _HitMax;	//! 引数を変数に代入

	return HitMax;		//! 上限を返す
}


bool HitStop::HitStoptime()
{
	if (HitJudge == false)
	{
		//! 座標をとる
		stoppos = mcpHitStopAnimation->GetVec();
	}

	//! ヒットストップ始まり
	if (HitStopFlg)		//! フラグが正の場合
	{
		//! 引数で渡された値になるまでカウント
		if (HitCount <= HitMax)
		{
			HitCount++;		//! カウント＋
			HitJudge = true;	//! 座標をとるのをやめる
			mcpHitStopAnimation->SetVec(stoppos);	//! とった座標でとどまり続ける
			mcpHitStopAnimation->GetAnimSprite()->SetAnimSpeed(300);	//! アニメーションスピードを下げてとまっているように見せる
		}
		if (HitCount >= HitMax)		//! 上限いったら
		{
			HitStopFlg = false;		//! ヒットストップフラグのリセット
			HitJudge = false;		//! 座標フラグのリセット
			HitCount = 0;			//! カウントのリセット
			HitMax = 0;				//! 上限のリセット
			mcpHitStopAnimation->GetAnimSprite()->SetAnimSpeed(8);		//! アニメーションスピードを元に戻す
		}
	}
	return HitStopFlg;		//! ヒットストップフラグを返す　※大体false
}

//! 座標を取るかどうかのゲッター
bool HitStop::GetHitJugde()
{
	return HitJudge;		//! 座標フラグを返す
}

