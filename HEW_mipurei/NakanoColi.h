#pragma once
#include"Box.h"
#include"Circle.h"
/*
//制作者：仲野睦基
//円と矩形の当たり判定を作ってます(11月12日時点)
//完成したら、Colisionクラスにくっつけてください。お願いします。
*/
class NakanoColi
{
public:
	static bool Box_Circle(Box* _Box,Circle* _Circle);//円と矩形の当たり判定
	static float DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY);//距離の測定
};