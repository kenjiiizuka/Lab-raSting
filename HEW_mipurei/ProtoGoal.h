#pragma once
#include "AnimationHitObject.h"
#include"Box.h"
class ProtoGoal :
	public AnimationHitObject
	/*
	制作者：仲野睦基
	ゴール地点のクラスです。
	ゴールしたフラグのゲッターを持っており、それでゴールしたことを検知させます。
	*/
{
public:
	ProtoGoal();
	ProtoGoal(float _X, float _Y);
	~ProtoGoal();
	void Update();
	void Draw();
	Box* GetmpGoalBox();
	//当たり判定1回目を取得するフラグ
	bool GetFirstStabFlg();
	void SetFirstStabFlg(bool _Flg);
	//当たり判定2回目を取得するフラグ
	bool GetSecondStabFlg();
	void SetSecondStabFlg(bool _Flg);
private:
	ID3D11ShaderResourceView * GoalTex;
	//当たり判定確認用画像
	Image mcImage;
	//ゴールの当たり判定
	Box* mpGoalCollisionBox;
	Vector2 GoalColiPos;
	//最初にゴールにプラグを突き刺した判定をするフラグ
	bool FirstStabFlg;
	//2回目に勢いよくプラグを突き刺した判定をするフラグ
	bool SecondStabFlg;
};