#pragma once
#include "Sprite.h"

//! アニメーションスプライトクラス　
//! UV座標が左上(0,0)に対応しています

class AnimationSprite :
	public Sprite
{
public:	
	AnimationSprite(Vector2 & _pos);
	~AnimationSprite();
	void Update() override;
	void SetAnimtionTable(int _xsplit, int _ysplit); //! アニメーション情報のセッター(そのテクスチャの縦横の分割数)
	void SetAnimSpeed(int _animspeed);               //! アニメーションスピードのセッター   
	void SetYSplit(int _ysplit);                     //! 縦方向のアニメーションのコマ番号のセッター
	void SetXSplit(int _xsplit);                     //! X方向のアニメーションのコマ番号のセッター
	void ResetAnimCnt();
	void SetStopAnimation(bool _state);              //! アニメーションを止めるためのせったー
	void SetNoStopObj(bool _state);              
	int GetCurrentXSplit();             //! 今再生しているアニメーションが横方向で何番目なのかを返す

private:
	int* mpAnimTable;      //! ア二メーションテーブル
	int mAnimTableElemnt;  //! アニメーションテーブルの要素数
	int mAnimSpeed;        //! アニメーションスピード
	int mAnimCnt;          //! アニメーションカウント
	int mYSplit;           //! Y方向の位置
	int mCurrentXsplit;    //! 今のX方向の位置
	bool StopAnimation;    //! アニメーションを止める

	bool NoStopObj = false;        //! ポーズ画面用のアニメーションがとまらないオブジェクトです
};

