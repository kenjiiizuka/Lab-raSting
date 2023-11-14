#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "PlayerState.h"
#include "Image.h"
#include "AnimationHitObject.h"
/* ------------- 
// ごーるです */

class Goal :
	public AnimationHitObject
{
public:
	Goal();
	~Goal();

	void Update();
	void Draw();

	Box * GetBoxCol();
	bool GetGoal();    //! ゴールしたかをもらう
	TailReaction ReturnReaction(float _power);
	bool GetHit();                //! ヒットしたかのゲッター ゴールに尻尾をさしたら音をとめるために
	void SetGoaled(bool _goaled); //! ゴールしたことにする
private:
	Box * mcpBox;
	bool Start;                          //! 演出が始まるフラグ
	AnimationHitObject * PeaperStream;
	int YSplit;
	bool Hit;
	bool Hited;
	bool mGoal;
	int FrameCnt; //! ゴールの演出のためのフレームを数える
};

