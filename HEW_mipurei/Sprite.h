#pragma once
#include "Vector2.h"
#include "direct3d.h"
#include "VERTEX2D.h"
#include "FLOAT2.h"
// 静止画の描画クラス　

class Sprite
{	
public:
	Sprite(Vector2 & _pos);
	virtual ~Sprite();
	virtual void Update();
	void Draw();

	void SetTexture(ID3D11ShaderResourceView* _texture);                             //! テクスチャのセッター
	void SetSize(float _width, float _vertical);                                     //! 描画サイスのセッター
	void SetUVSpriteInf(int _num, int xsplit, int splity, bool _state = true);       //! UV情報のセッター
	void SetAngle(double _angle, float _centerx = 0.5f, float _centery = 0.5f);      //! 回転角度、回転の中心のセッター
	void SetColor(float _r, float _g, float _b);                                     //! 色情報のセッター
	void SetArufa(float _a);                                                         //! 透明度のセッター
	void SetTexNum(int _num, int xsplit, int splity,bool _state = true);             //! セットされているテクスチャの何コマ目を描画してほしかをセットする(チップ状の画像限定です)
	                                                         //! アニメーションカウントをリセット
protected:
	// メンバ変数
	ID3D11ShaderResourceView* mTexture; //! テクスチャ
	ID3D11Buffer* mVertexBuffer;        //! 頂点バッファ
	Vector2 & msPos;			        //! 中心座標
	FLOAT2  msSize;					//! 描画サイズ
	float mPosU, mPosV;                 //! UV座標
	float mSizeU, mSizeV;               //! UVのサイズ・・・テクスチャの描画範囲
	double  mAngle;				        //! 描画角度
	float mCenterX, mCenterY;           //! 回転の中心位置
	RGBA msColor;                       //! 色

private:
	int TexNum;                         //! チップ上の座標の何コマ目を描画してほしいのかのセッター
	int XSplit;                         //! 横の分割数
	int YSplit;                  		//! 縦の分割数
	bool SplitDraw;                     //! コマをしていして描画するときの
};
