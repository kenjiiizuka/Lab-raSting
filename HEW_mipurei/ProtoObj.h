#pragma once
#include "Character.h"
#include"Box.h"
//====================================================//
/*
プロトタイプ版マップの当たり判定用に使うキャラクターです
作成者：仲野睦基
*/
//====================================================//
class ProtoObj :
	public Character
{
public:
	ProtoObj();
	~ProtoObj();
	void Update() override;
	void Draw() override;
	//Vector2* GetVec2();//mcpvecを返すための関数(当たり判定用)
	void AddVec2(float _x, float _y);//float型で位置を指定する
	Box* GetmpBox();
private:
	Box* mpBox;
};

