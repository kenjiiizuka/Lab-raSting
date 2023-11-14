#pragma once
#include "Gimmick.h"
#include"Box.h"
/*
大きなドアのクラスです。(シャッターみたいな動き？)
制作開始日：2022/11/21
制作者：仲野睦基
*/

class BigDoor :
	public Gimmick
{
public:
	BigDoor();//初期位置指定をするコンストラクタ
	~BigDoor();
	void Update();
private:
	float mTotal; //! 移動した量
	int mFrameCnt; //! フレームを数える
};

