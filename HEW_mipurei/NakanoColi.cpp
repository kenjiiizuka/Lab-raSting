#include "NakanoColi.h"

/* --------------------------------------------------------------
//円と矩形の当たり判定                                         //
// 引数　 : _Box, _Circle                                      //
// 戻り値 : 当たっているかどうか                               */
bool NakanoColi::Box_Circle(Box* _Box, Circle* _Circle)
{
	//今の状態では、当たり続けると思うので、処理が完成したらColisionクラス内にあるActive確認関数を用意する

	bool TmpFlg = false;//ローカル変数。この関数内での当たり判定に使う

	//矩形側の準備
	float Left = _Box->GetVec().x - _Box->GetSize().x / 2;
	float Right = Left + _Box->GetSize().x;
	float Bottom = _Box->GetVec().y - _Box->GetSize().y / 2;
	float Top = Bottom + _Box->GetSize().y;

	// 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
	if ((_Circle->GetVec().x > Left - _Circle->GetRadiuse()) &&
		(_Circle->GetVec().x < Right + _Circle->GetRadiuse()) &&
		(_Circle->GetVec().y > Top - _Circle->GetRadiuse()) &&
		(_Circle->GetVec().y < Bottom + _Circle->GetRadiuse()))
	{
		TmpFlg = true;
		float Radiuse2jou = _Circle->GetRadiuse() *  _Circle->GetRadiuse();


		// 左
		if (_Circle->GetVec().x < Left)
		{
			// 左上
			if ((_Circle->GetVec().y < Top))
			{
				if ((DistanceBox_Circle(Left, Top, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
				{
					TmpFlg = false;
				}
			}
			else
			{
				// 左下
				if ((_Circle->GetVec().y > Bottom))
				{
					if ((DistanceBox_Circle(Left, Bottom, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
					{
						TmpFlg = false;
					}
				}
			}
		}
		else
		{
			// 右
			if (_Circle->GetVec().x >Right)
			{
				// 右上
				if ((_Circle->GetVec().y < Top))
				{
					if ((DistanceBox_Circle(Right, Top, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
					{
						TmpFlg = false;
					}
				}
				else
				{
					// 右下
					if ((_Circle->GetVec().y > Bottom))
					{
						if ((DistanceBox_Circle(Right, Bottom, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
						{
							TmpFlg = false;
						}
					}
				}
			}
		}
	}

	return TmpFlg;
}

/* --------------------------------------------------------------
//オブジェクト同士の中心座標距離測定                           //
// 引数　 : _Box, _CircleのX,Y座標                             //
// 戻り値 : 計算結果を2乗して、足した数                        */
float NakanoColi::DistanceBox_Circle(const float _BoxX, const  float _BoxY, const float _CircleX, const float _CircleY)
{
	float dx = _CircleX - _BoxX;
	float dy = _CircleY - _BoxY;

	//2乗するので、正規化の必要なし？
	return (dx * dx) + (dy * dy);
}


