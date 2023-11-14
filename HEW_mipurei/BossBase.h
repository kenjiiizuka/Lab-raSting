#pragma once
#include "Character.h"
/*
ゲームに登場するボスの基底クラスです。これを派生させて、ボス本体を作ります。
制作開始日：2022/11/21
制作者：仲野睦基
*/
class BossBase :
	public Character
{
public:
	BossBase();
	~BossBase();
	virtual void Update();
	virtual void Draw();
};

