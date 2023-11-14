#include "Collision.h"
#include <math.h>
#include <algorithm>
#include "Log.h"
#include "ObjTag.h"

//! どの辺が最少の値なのか判断するためのマクロ
#define LEFT_MINIMUM 0
#define RIGHT_MINIMUM 1
#define TOP_MINIMUM 2
#define BOTTOM_MINIMUM 3


/*-------------------------------------------------------------------------------------------- - */
// 点と矩形の当たり判定関数                                              //
// 引数   : Shapeクラス , Boxクラス                                      //
// 戻り値 : 当たっているかどうか                                         //
bool Collision::Point_Box_Hit(Shape _pos1, Box _box2)
{	
	if (CheckActiv(_pos1, _box2)) {

		//! 矩形の各辺に位置を求める
		float Left = _box2.GetVec().x - _box2.GetSize().x / 2;
		float Right = Left + _box2.GetSize().x;
		float Bottom = _box2.GetVec().y - _box2.GetSize().y / 2;
		float Top = Bottom + _box2.GetSize().y;


		//! 点が矩形内に入っているかを判定する
		if (Left <= _pos1.GetVec().x && Right >= _pos1.GetVec().x && Bottom <= _pos1.GetVec().y && Top >= _pos1.GetVec().y) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

/* --------------------------------------------------------------
// 矩形と矩形の当たり判定                                      //
// 引数　 : Box1, Box2                                         //
// 戻り値 : 当たっているかどうか                               */
bool Collision::Box_Box_Hit(Box _box1, Box _box2)
{
	if (CheckActiv(_box1, _box2)) {
		//! 矩形1の各辺を求める
		float Left1 = _box1.GetLeft();
		float Right1 = _box1.GetRight();
		float Bottom1 = _box1.GetBottom();
		float Top1 = _box1.GetTop();

		//! 矩形2の各辺に位置を求める
		float Left2 = _box2.GetLeft();
		float Right2 = _box2.GetRight();
		float Bottom2 = _box2.GetBottom();
		float Top2 = _box2.GetTop();

		return Right2 >= Left1 && Right1 >= Left2 && Top1 >= Bottom2 && Top2 >= Bottom1;
	}
	return false;
}

/* ------------------------------ 
// Mapのアイテムとの当たり判定 */
bool Collision::Box_MapItem(Box _box1, float _mapwidht, float _mapheight, Vector2 _pos)
{
	//! 対象の矩形との距離を調べる
	_box1.GetSize();
	float dis = fabs(_box1.GetVec().x - _pos.x);                     //! 中心座標から距離
	float HitDis = (_mapwidht / 2) + (_box1.GetSize().x / 2); //! 当たる可能性のある距離小数点の誤差を考慮して距離は少し短めにする
	if (dis > HitDis) {
		return false;
	}

	if (_box1.GetActiv()) {
		//! 矩形1の各辺を求める
		float Left1 = _box1.GetLeft();
		float Right1 = _box1.GetRight();
		float Bottom1 = _box1.GetBottom();
		float Top1 = _box1.GetTop();

		//! 矩形2の各辺に位置を求める
		float Left2 = _pos.x - _mapwidht * 0.5f;
		float Right2 = Left2 + _mapwidht;
		float Bottom2 = _pos.y - _mapheight * 0.5f;
		float Top2 = Bottom2 + _mapheight;

		return Right2 >= Left1 && Right1 >= Left2 && Top1 >= Bottom2 && Top2 >= Bottom1;
	}

	return false;
}

//! プレイヤーの尻尾とマップのアイテムの当たり判定です
bool Collision::Circle_MapItem(Circle _circle, float _width, float _hieght, Vector2 _pos)
{
	
	float Rad = _circle.GetRadiuse();     //! 半径の取得
	Vector2 CirclePos = _circle.GetVec(); //! 円の位置の取得
	//! 各辺の取得
	float Left = _pos.x - _width * 0.5f;
	float Right = Left + _width;
	float Top = _pos.y + _hieght * 0.5f;
	float Bottom = Top - _hieght;
	Truncation_Box(&Left, &Right, &Top, &Bottom); //! 小数点の切り捨て

	//! 当たりの領域を計算する
	//! 縦方向
	float Region_Top = Top + Rad;
	float Region_Bottom = Bottom - Rad;
	//! 横方向
	float Region_Left = Left - Rad;
	float Region_Right = Right + Rad;

	//! 縦横の領域との当たりを判定する
	if (Region_Top > CirclePos.y && Region_Bottom < CirclePos.y && Region_Left < CirclePos.x && Region_Right > CirclePos.x) {
		//! 各頂点からどのくらい離れているのかを計算する
		float Rad2 = Rad * Rad; //! 半径の2乗
		float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
		float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
		float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
		float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

		if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
			return true;
		}
	}	
	return false;
}


/* ------------------------------------------------------------
// 円と円の当たり判定関数                                    //
// 引数   : Circle1, Circle2                                 //
// 戻り値 : 当たっているかどうか                             */
bool Collision::Circle_Circle_Hit(Circle _circle1, Circle _circle2)
{
	if (CheckActiv(_circle1, _circle2)) {

		//! 中心座標同士の距離を計算する
		float ptpx = _circle1.GetVec().x - _circle2.GetVec().x;
		float ptpy = _circle1.GetVec().y - _circle2.GetVec().y;
		float ptp = (ptpx * ptpx) + (ptpy * ptpy);
		//! 半径１と半径２を足した長さ
		float h1h2 = _circle1.GetRadiuse() + _circle2.GetRadiuse();

		return h1h2 * h1h2 > ptp;
	}
	return false;
}



/* --------------------------------------------- 
// 動いてるオブジェクト同士の当たり判定       //
// 引数 矩形の情報、矩形の情報                */
bool Collision::Box_Box_Collision(Box & _box1, Box & _box2)
{
	//! 当たり判定がオンになっているかチェックする
	if (CheckActiv(_box1, _box2)) {

		//! 横方向の距離とあたる可能性のある距離と比べる
		//! 当たる可能性のある距離じゃなかったらfalse
		
		float Dis = fabs(_box1.GetVec().x - _box2.GetVec().x);
		float HitDis = (_box1.GetSize().x / 2) + (_box2.GetSize().x / 2);
		if (Dis > HitDis) {
			return false;
		}

		//! それぞれの座標を取得
		Vector2 Vec_Box1 = _box1.GetVec();
		Vector2 Vec_Box2 = _box2.GetVec();

		//! 矩形1の各辺を求める
		float CLeft = _box1.GetLeft();
		float CRight = _box1.GetRight();
		float CTop = _box1.GetTop();
		float CBottom = _box1.GetBottom();	
		Truncation_Box(&CLeft, &CRight, &CTop, &CBottom); //! 小数点以下の切り捨て

		//! 矩形2の各辺に位置を求める
		float Left = _box2.GetLeft();
		float Right = _box2.GetRight();
		float Bottom = _box2.GetBottom();
		float Top = _box2.GetTop();
		Truncation_Box(&Left, &Right, &Top, &Bottom); //! 切り捨て

		if (Right >= CLeft && CRight >= Left && CTop >= Bottom && Top >= CBottom) {

			//! 動いてる量を取得
			Vector2 MoveVec_Box1 = _box1.GetMoveVec();
			Vector2 MoveVec_Box2 = _box2.GetMoveVec();
			Shape * point = _box1.Getthis();
			if (MoveVec_Box1 == 0.0f && MoveVec_Box2 == 0.0f) {
				StaticBox_StaticBox(_box1, _box2);								
			}
			//! Box1がうごいていない時	
			else if (MoveVec_Box1 == 0.0f) {
				Box_StaticBox(_box2, _box1);
			}
			//! Box2が動いていない時
			else if (MoveVec_Box2 == 0.0f) {				
 				Box_StaticBox(_box1, _box2);
			}
			//! どちらも動いてる時
			else {		
				//! 修正距離を出す
				float FixTop =  Top - CBottom ; //! 上への修正量
				float FixBottom = CTop - Bottom ; //! 下への修正量
				float FixLeft = CRight - Left; //! 左への修正量
				float FixRight = Right - CLeft; // ! 右への修正量

				//! めり込んでいる量が一番すくない方向を修正する
				int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
				if (Minimum == LEFT_MINIMUM) { //! 左側からあたっている場合
					//! どちらも動いているとき
					if (MoveVec_Box1.x != 0 && MoveVec_Box2.x != 0) {
						_box1.SetX(Vec_Box1.x - FixLeft / 2.0f);
						_box2.SetX(Vec_Box2.x + FixLeft / 2.0f);
					}
					//! Box1だけ動いてるとき
					else if (MoveVec_Box1.x != 0 && MoveVec_Box2.x == 0) {
						_box1.SetX(Vec_Box1.x - FixLeft);
					}
					//! Box2だけうごいてる時
					else {
						_box2.SetX(Vec_Box2.x + FixLeft);
					}
				}
				else if (Minimum == RIGHT_MINIMUM) { //! 右側から当たっている時
					//! どちらも動いてる時
					if (MoveVec_Box1.x != 0 && MoveVec_Box2.x != 0) {
						_box1.SetX(Vec_Box1.x + FixRight / 2.0f);
						_box2.SetX(Vec_Box2.x - FixRight / 2.0f);
					}
					//! Box1だけ動いてるとき
					else if (MoveVec_Box1.x != 0 && MoveVec_Box2.x == 0) {
						_box1.SetX(Vec_Box1.x + FixRight);
					}
					//! Box2だけ動いてるとき
					else {
						_box2.SetX(Vec_Box2.x - FixRight);
					}
				}
				else if (Minimum == TOP_MINIMUM) { //! 上から当たっているとき
					//! どちらも動いてる時
					if (MoveVec_Box1.y != 0 && MoveVec_Box2.y != 0) {
						_box1.SetY(Vec_Box1.y + FixTop / 2.0f);
						_box2.SetY(Vec_Box2.y - FixTop / 2.0f);					
					}
					//! Box1だけ動いてるとき
					else if (MoveVec_Box1.y != 0 && MoveVec_Box2.y == 0) {
						_box1.SetY(Vec_Box1.y + FixTop);
					}
					//! Box2だけ動いてるとき
					else {
						_box2.SetY(Vec_Box2.y - FixTop);
					}

					//! 上にいる方のフラグを立てる
					if (Vec_Box1.y > Vec_Box2.y) {
						_box1.SetOnObj(true);
					}
					else {
						_box2.SetOnObj(true);
					}
				}
				else if (Minimum == BOTTOM_MINIMUM) { //! 下から当たってる時
					if (MoveVec_Box1.y != 0 && MoveVec_Box2.y != 0) {
						_box1.SetY(Vec_Box1.y - FixBottom / 2.0f);
						_box2.SetY(Vec_Box2.y + FixBottom / 2.0f);					
					}
					else if (MoveVec_Box1.y != 0 && MoveVec_Box2.y == 0) {
						_box1.SetY(Vec_Box1.y - FixBottom);
					}
					else {
						_box2.SetY(Vec_Box2.y + FixBottom);	
					}
					//! 上にいる方のフラグを立てる
					if (Vec_Box1.y > Vec_Box2.y) {
						_box1.SetOnObj(true);
					}
					else {
						_box2.SetOnObj(true);	
					}
				}				
			}
			//! 当たっていたら
			return true;
		}	
		return false;
	}
	return false;
}


/* ------------------------------------------------------ 
// 一方が動いていない矩形の当たり判定処理*/
void Collision::Box_StaticBox(Box & _box1, Box & _box2)
{
	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();
	//! 小数点以下の切り捨て
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	//! 矩形2の各辺に位置を求める
	float Left = _box2.GetLeft();
	float Right = _box2.GetRight();
	float Bottom = _box2.GetBottom();
	float Top = _box2.GetTop();
	//! 切り捨て	
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! 各方向への修正量をだす
	float FixTop = Top - CBottom;          //! 上への修正量
	float FixBottom = CTop - Bottom;       //! 下への修正量
	float FixLeft = CRight - Left;         //! 左への修正量
	float FixRight = Right - CLeft;        //! 右への修正量
	//! 修正する量が一番小さい方向に修正する
	int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
	if (Minimum == LEFT_MINIMUM) { //! 左側からあたっている場合
		_box1.SetX(_box1.GetVec().x - FixLeft);
	}
	else if (Minimum == RIGHT_MINIMUM) { //! 右側から当たっている時
		_box1.SetX(_box1.GetVec().x + FixRight);
	}
	else if (Minimum == TOP_MINIMUM) { //! 上から当たっているとき
		//! 上に移動していたら修正しない
		if (!(_box1.GetMoveVec().y >= 0.0f)) {
			_box1.SetY(_box1.GetVec().y + FixTop);
			_box1.SetOnObj(true);
		}       
	}
	else if (Minimum == BOTTOM_MINIMUM) { //! 下から当たってる時
		_box1.SetY(_box1.GetVec().y - FixBottom);
	}	
}

/* ------------------------------------------- 
// どちらも静止している矩形の当たり判定関数 */
void Collision::StaticBox_StaticBox(Box & _box1, Box & _box2)
{
	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();
	//! 小数点以下の切り捨て
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	float bx = floorf(_box2.GetVec().x * 1000) / 1000;
	float by = floorf(_box2.GetVec().y * 1000) / 1000;

	//! 矩形2の各辺に位置を求める
	float Left = _box2.GetLeft();
	float Right = _box2.GetRight();
	float Bottom = _box2.GetBottom();
	float Top = _box2.GetTop();
	//! 切り捨て	
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! 各方向への修正量をだす
	float FixTop = Top - CBottom;    //! 上への修正量
	float FixBottom = CTop - Bottom; //! 下への修正量
	float FixLeft = CRight - Left;   //! 左への修正量
	float FixRight = Right - CLeft;  //! 右への修正量
	//! 修正する量が一番小さい方向に修正する

	int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);	
	if (Minimum == TOP_MINIMUM) { //! 上から当たっているとき
		_box1.SetOnObj(true);			
	}
	else if (Minimum == BOTTOM_MINIMUM){
		_box2.SetOnObj(true);
	}
}
/* ------------------------------------------
// 矩形と円の当たり判定を取る関数          //
// 引数   : 矩形 , 円                      //
// 戻り値 : 当たっているかどうか           */
bool Collision::Box_Circle_Hit(Box _Box, Circle _Circle)
{	
	float dis = fabs(_Box.GetVec().x - _Circle.GetVec().x);
	float HitDis = _Box.GetSize().x + _Circle.GetRadiuse();
	if (dis > HitDis) {
		return false;
	}

	if (CheckActiv(_Box, _Circle)) {
		float Rad = _Circle.GetRadiuse();     //! 半径の取得
		Vector2 CirclePos = _Circle.GetVec(); //! 円の位置の取得
		//! 各辺の取得
		float Left = _Box.GetLeft();
		float Right = _Box.GetRight();
		float Top = _Box.GetTop();
		float Bottom = _Box.GetBottom();
		Truncation_Box(&Left, &Right, &Top, &Bottom); //! 小数点の切り捨て

		//! 当たりの領域を計算する
		//! 縦方向
		float Region_Top = Top + Rad;
		float Region_Bottom = Bottom - Rad;
		//! 横方向
		float Region_Left = Left - Rad;
		float Region_Right = Right + Rad;

		//! 縦横の領域との当たりを判定する
		if ((Region_Top > CirclePos.y) && (Region_Bottom < CirclePos.y) && (Region_Left < CirclePos.x) && (Region_Right > CirclePos.x)) {
			//! 各頂点からどのくらい離れているのかを計算する
			float Rad2 = Rad * Rad; //! 半径の2乗
			float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
			float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
			float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
			float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

			if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
				return true;
			}
		}
	}
	return false;
}

/* -----------------------------------------
// 矩形と円の距離をはかる関数             //
// 引数   : 矩形と円の中心座標            //
// 戻り値 : 距離                          */
float Collision::DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY)
{
	float dx = _CircleX - _BoxX;
	float dy = _CircleY - _BoxY;

	//2乗するので、正規化の必要なし？
	return (dx * dx) + (dy * dy);
}

/* ------------------------------------- 
// しっぽ(攻撃時)とマップの当たり判定 */
bool Collision::Tail_Map(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos)
{
	if (_circle.GetActiv()) {
		float Rad = _circle.GetRadiuse();
		Vector2 CirclePos = _circle.GetVec();
		float bx = floorf(_pos.x * 1000) / 1000;
		float by = floorf(_pos.y * 1000) / 1000;
		//! 矩形2の各辺に位置を求める
		float Left = bx - (_mapwidht * 0.5f);
		float Right = Left + _mapwidht;
		float Bottom = by - (_mapheight * 0.5f);
		float Top = Bottom + _mapheight;
		//! 切り捨て
		Truncation_Box(&Left, &Right, &Top, &Bottom);

		//! 当たりの領域を計算する
		//! 縦方向
		float Region_Top = Top + Rad;
		float Region_Bottom = Bottom - Rad;
		//! 横方向
		float Region_Left = Left - Rad;
		float Region_Right = Right + Rad;

		//! 縦横の領域との当たりを判定する
		if (Region_Top > CirclePos.y && Region_Bottom < CirclePos.y && Region_Left < CirclePos.x && Region_Right > CirclePos.x) {
			//! 各頂点からどのくらい離れているのかを計算する
			float Rad2 = Rad * Rad; //! 半径の2乗
			float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
			float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
			float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
			float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

			if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
				return true;
			}
		}
	}
	return false;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------- */
// マップ用の当たり判定　(矩形)　　　　　　　　　　　　                                                                                 　　　//
// 引数 : 矩形のキャラの当たり判定情報 , マップチップの横幅, マップチップの立幅 , マップチップの位置 ,　各面に対して既に当たっているかのフラグ//
// 戻り値 : 地面に触れているか
bool Collision::Box_BoxMap(Box & _box1, float _mapwidht, float _mapheight, Vector2 _pos)
{
	if (!_box1.GetActiv()) {
		return false;
	}

	bool TouchGround = false;

	//! 対象の矩形との距離を調べる
	_box1.GetSize();
	float dis = fabs(_box1.GetVec().x - _pos.x);                     //! 中心座標から距離
	float HitDis = (_mapwidht / 2) + (_box1.GetSize().x / 2); //! 当たる可能性のある距離小数点の誤差を考慮して距離は少し短めにする
	if (dis >  HitDis) {
		return false;
	}

	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();

	//! 小数点以下の切り捨て
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	float bx = floorf(_pos.x * 1000) / 1000;
	float by = floorf(_pos.y * 1000) / 1000;

	//! 矩形2の各辺に位置を求める
	float Left = bx - (_mapwidht * 0.5f);
	float Right = Left + _mapwidht;
	float Bottom = by - (_mapheight * 0.5f);
	float Top = Bottom + _mapheight;
	//! 切り捨て
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! 当たっているかを判断する
	if (Right >= CLeft && CRight >= Left && CTop >= Bottom && Top >= CBottom) {
		//! 各方向への修正量をだす
		float FixTop = Top - CBottom;    //! 上への修正量	    
		float FixBottom = CTop - Bottom; //! 下への修正量
		float FixLeft = CRight - Left;   //! 左への修正量
		float FixRight = Right - CLeft;  //! 右への修正量
		//! 修正する量が一番小さい方向に修正する
		int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
		if (Minimum == LEFT_MINIMUM) { //! 左側からあたっている場合
			_box1.SetX(_box1.GetVec().x - FixLeft);
		}
		else if (Minimum == RIGHT_MINIMUM) { //! 右側から当たっている時
			_box1.SetX(_box1.GetVec().x + FixRight);
		}
		else if (Minimum == TOP_MINIMUM) { //! 上から当たっているとき
			//! 上に移動していたら修正しない
			if (!(_box1.GetMoveVec().y > 0.0f)) {
				TouchGround = true; //! 上から当たるときは地面に触れている
				_box1.SetY(_box1.GetVec().y + FixTop);
			}
		}
		else if (Minimum == BOTTOM_MINIMUM) { //! 下から当たってる時
			_box1.SetY(_box1.GetVec().y - FixBottom);
		}
		
		return TouchGround;
	}

	return false;
}

//! 矩形用の小数点切り捨て関数
void Collision::Truncation_Box(float * _left, float * _right, float * _top, float * _bottom)
{
	*_left = floorf(*_left * 1000) / 1000;
	*_right = floorf(*_right * 1000) / 1000;
	*_top = floorf(*_top * 1000) / 1000;
	*_bottom = floorf(*_bottom * 1000) / 1000;
}

/*-------------------------------------------------------------
// 当たり判定切り替え用フラグのチェック関数                  //
// 引数 チェックしたい形状クラス1, チェックしたい形状クラス1 //
// 戻り値 : どちらも当たり判定がオンになっていればtrueを返す */
bool Collision::CheckActiv(Shape _shape1, Shape _shape2)
{
	if (_shape1.GetActiv() && _shape2.GetActiv()) {
		return  true;
	}
	return false;
}

/* -------------------------------------------------
// 引数の中からどれが最小なのかを消してくれる関数 */
int Collision::GetMinimum(float _left, float _right, float _top, float _bottom)
{
	float Array[4] = {_left, _right, _top, _bottom};
	int size = sizeof(Array) / sizeof(Array[0]);
	
	std::sort(Array,Array + size);
	
	if (Array[0] == _left) {
		return LEFT_MINIMUM;
	}
	else if (Array[0] == _right) {
		return RIGHT_MINIMUM;
	}
	else if (Array[0] == _top) {
		return TOP_MINIMUM;
	}	
	return BOTTOM_MINIMUM;
}