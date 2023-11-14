#pragma once
#include "AnimationHitObject.h"
#include"Box.h"

/*
ハンマーを持ったボスのトドメをさすときに、
攻撃する部分のクラスです。
*/
class Plag :
	public AnimationHitObject
{
public:
	Plag(float _x, float _y);
	~Plag();
	void Update();
	void Draw();
	//プレイヤーのしっぽと当たり判定をするための関数
	Box* GetPlagCollision();
private:
	ID3D11ShaderResourceView * mPlagTex;
	Box* mpPlagCollision;
	Vector2 mpPlagColisionPos;
	//当たり判定確認用画像
	Image mcImage;
};

