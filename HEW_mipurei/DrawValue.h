#pragma once
#include "Image.h"
#include "direct3d.h"
#include <math.h>

/* --------------------------------------------------------------------------------------------
// 数値を描画してくれるクラスです                                                            //
// Draw関数の第一引数に描画したい変数(数値)を設定することで少数第４位まで描画してくれます。  //
// 描画位置、描画サイズ、RGBAも変更可能です。                                                //
// ※ yの位置をの方を変更することが多くなると思うので、yを第二引数にしています。             */
class DrawValue
{
public:
	DrawValue(); //! コンストラクタ
	~DrawValue(); //! デストラクタ

	//! 引数の値を描画してくれます。
	//! 第二引数以降を設定しなかったら画面左上に描画されます 改行するためにｙ座標を変えたい場合を多いと思うので第二引数にｙを持ってきています
	template <typename T> void Draw(T _value , float _y = 0.9f, float _x = -1.8f, float _width = 0.06f, float _height = 0.06f,float _r = 1.0f , float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); //! もらった変数を描画する機能
private:
	Image *mcpImage; //! 描画クラス
	ID3D11ShaderResourceView * ValueGraph[10]; //! 数字の画像
	ID3D11ShaderResourceView * Decimal;        //! 小数点の画像
	ID3D11ShaderResourceView * Minus;          //! マイナスの画像

};

template<typename T>
inline void DrawValue::Draw(T _value ,float _y, float _x, float _width, float _height, float _r, float _g, float _b, float _a)
{
	T tmp = _value;
		
	if (tmp == false || tmp == true) {
		if (tmp) {
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[1], _r, _g, _b, _a);
		}
		else {
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[0], _r, _g, _b, _a);
		}
	}
	else {
		//! 値が正か負判断する //負ならーを描画する
		if (_value < 0) {
			mcpImage->DrawSprite(_x, _y, _width, _height, Minus, _r, _g, _b, _a);
			_x += _width;
			tmp *= -1; //! 正の値にする
		}
		//! 値が何桁か数える
		//! 0を下回るまで10で割っていき割れた回数をで桁数を判断する	
		int Digit;  //! 桁数
		for (Digit = 0; tmp > 1; Digit++) {
			tmp /= 10.0f;
		}
		tmp *= 10; //! 一桁の値にする

		for (int num = 0; num < Digit + 4; num++) {

			//! 桁数分描画したら小数点を描画する
			if (num == Digit) {
				if (num == 0) {
					mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[0], _r, _g, _b, _a);
					_x += _width;
				}
				mcpImage->DrawSprite(_x, _y, _width, _height, Decimal, _r, _g, _b, _a);
				_x += _width;
				tmp += 0.0001f;
			}

			T prev = tmp;
			int Value = floor(tmp); //! 小数点以下切り下げ これで一桁目の数字がわかる
			//! 数字の描画
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[Value], _r, _g, _b, _a);
			_x += _width;

			tmp -= Value;
			tmp *= 10;
		}
	}
}
