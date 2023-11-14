#pragma once
#include "AnimationHitObject.h"

//! テクスチャがひろってきたやつなので、専用に作ります
class Smoke :
	public AnimationHitObject
{
	enum SmokeState {
		State_FadeIn,
		State_FadeOut,
		State_None,
	};
public:
	Smoke();
	~Smoke();

	void Update();
	void Draw();

	//! 煙を出す用の関数
	void NomalSmokeSmall(Vector2 _pos);   //! 真上に向かってでる煙
	void LeftSmokeSmall(Vector2 _pos);    //! 左上に向かってでる煙
	void RightSmokeSmall(Vector2 _pos);   //! 右上に向かってでる煙
	void NomalSmokeRagular(Vector2 _pos); //! 真上に向かってでる煙(中)
	void SmokeOff();        //! 煙のアニメションをやめる
	bool GetSmokeActiv();   //! 煙が今出ているかを取得する
private:
	SmokeState State;
	bool SmokeActiv = false;
	float Arufa;
};

