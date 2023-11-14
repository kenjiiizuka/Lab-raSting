#pragma once
#include "FLOAT2.h"
#include "Box.h"
#include "Circle.h"
#include "Vector2.h"
#include "Character.h"
//------------------------------------------------------
// 当たり判定クラス（仮）試したい時などに使うようです
// 制作者 : 飯塚 健司


#define PBH(_point, _box, _hit)  _hit = Collision::Point_Box_Hit(_point, _box)
#define BBC(_box1, _box2)        Collision::Box_Box_Collision(_box1,_box2) 
#define BBH(_box1, _box2)       Collision::Box_Box_Hit(_box1, _box2)
#define BCH(_box, _circle)      Collision::Box_Circle_Hit(_box, _circle)


class Collision
{
public:
	static bool Point_Box_Hit(Shape _box1, Box _box2);                         //! 点と矩形の当たり判定を取る関数
	static bool Box_Box_Hit(Box _box1, Box _box2);                             //! 矩形と矩形の当たり判定
	static bool Box_MapItem(Box _box1, float _mapwidht, float _mapheight, Vector2 _pos);
	static bool Circle_MapItem(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos);
	static bool Circle_Circle_Hit(Circle _circle1, Circle _circle2);           //! 円と円の当たり判定  動作確認していません
	static bool Box_Box_Collision(Box & _box1, Box & _box2);                   //! 矩形のオブジェクトの当たり判定 (動いてるオブジェクト)
	//static bool BoxChar_BoxChar(Character & _charbox1, Character & _chrabox2); //! 矩形のキャラ同士の当たり判定
	static bool Box_Circle_Hit(Box _Box, Circle _Circle);                        //! 円と矩形の当たり判定
	static float DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY);//距離の測定

	//! MAP用の当たり判定です
	static bool Tail_Map(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos);  //! マップとしっぽの当たり判定
	static bool Box_BoxMap(Box & _box1, float _mapwidht, float _mapheight, Vector2 _pos);    //! 矩形のキャラと矩形の当たり判定　引数１が引数２にめり込んでる量を返してくれる
	//! 小数点の切り捨て
	static void  Truncation_Box(float * _left, float * _right, float * _top, float * _bottom);

private:
	static void Box_StaticBox(Box & _box1, Box & _box2);  //! 引数２が動いてないときの矩形の衝突判定関数
	static void StaticBox_StaticBox(Box & _box1, Box & _box2); //! どちらも静止している矩形の衝突判定関数
	static bool CheckActiv(Shape _shape1, Shape _shape2); //! 当たり判定切り替えようフラグのチェック関数
	static int GetMinimum(float _left, float _right , float _top, float _bottom); //! 矩形の当たり判定の応答処理で使う引数の中から最少を返す関数
};



