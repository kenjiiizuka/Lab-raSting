// コマンド選択に用いるカーソルクラス
// 縦方向にのみ対応可

#pragma once

#include "Image.h"
#include "FLOAT2.h"

class SelectCursol
{
public:
	int Update(); // 戻り値にえらんだコマンドを返す なにも選んでいない時は-1が来る
	void Draw();
	~SelectCursol();
	SelectCursol(int num, float xPos, float yPos, float Interval, float width); // コマンドの数と最初のコマンドの座標を渡す 
private:
	int mNumComnd; //コマンドの数
	int mSelectComand;  // 今どのコマンドをえらんでいるか
	int mOldSelectComand; // 前フレームに選んでいたコマンド
	float mInterval;
	// コマンドの移動制限に使う
	float mComnadTopPos; // 一番上のコマンドのY座標
	float mComnadUnderPos; // 一番下のコマンドのX座標
	Image *mpcImage;
	FLOAT2* mpComandPos;
	FLOAT2 msPos;
	FLOAT2 msOldPos;

	// 受け取ったコマンドの数と座標からそれぞれのこまんどの位置を計算する
};

