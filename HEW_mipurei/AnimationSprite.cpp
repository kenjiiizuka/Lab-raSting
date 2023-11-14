#include "AnimationSprite.h"
#include "VERTEX2D.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"
#include "GameManager.h"

//! コンストラクタ
AnimationSprite::AnimationSprite(Vector2 & _pos) : Sprite::Sprite(_pos)
{
	mAnimSpeed = 8;
	mAnimCnt = 0;
	mYSplit = mCurrentXsplit = 0;
	mAnimTableElemnt = 4;
	StopAnimation = false;
	//! アニメーションテーブルの初期値設定　横３分割、縦４分割　作るゲームの素材で一番多い分割に合わせて設定するようにすると良い
    mpAnimTable = new int[mAnimTableElemnt];
	mpAnimTable[0] = 0;
	mpAnimTable[1] = 1;
	mpAnimTable[2] = 2;
	mpAnimTable[3] = 1;

	//! １コマのUVサイズ
	mSizeU = (1.0f / 3.0f);
	mSizeV = (1.0f / 4.0f);	
}


//! デストラクタ
AnimationSprite::~AnimationSprite()
{	
	delete[] mpAnimTable;
	mpAnimTable = nullptr;
}


//! 更新処理
void AnimationSprite::Update()
{	
	VERTEX2D vx[4];     //! 四頂点の位置	
	VERTEX2D vertex[6]; //! 頂点の設定　バッファに送る用

	int XSplit;
	//! UV座標を計算する
	if (mAnimTableElemnt != 0) 
	{
		int Index = (mAnimCnt / mAnimSpeed) % mAnimTableElemnt; // アニメーションテーブルの添え字	
		XSplit = mpAnimTable[Index];
		mCurrentXsplit = XSplit;
	}
	else 
	{
		XSplit = 0;
	}

	float uLeft = mSizeU * XSplit;
	float uRight = uLeft + mSizeU;
	float vTop = mSizeV * mYSplit;
	float vBottom = vTop + mSizeV;

	//! 角度を設定していない場合
	if (mAngle == 0.0f) {
		vx[LEFTDOWN] = { msPos.x - msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uLeft,vBottom, msColor };
		vx[RIGHTDOWN] = { msPos.x + msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uRight,vBottom, msColor };
		vx[LEFTTOP] = { msPos.x - msSize.x / 2.0f , msPos.y + msSize.y / 2.0f ,uLeft,vTop, msColor };
		vx[RIGHTTOP] = { msPos.x + msSize.x / 2.0f , msPos.y + msSize.y / 2.0f ,uRight,vTop, msColor };

	}
	else {
		float  Hypotenuse; //! 斜辺
		double Rad;        //! ラジアン
		//! 右上
		Hypotenuse = (float)sqrt(pow(msSize.x * (1 - mCenterX), 2.0f) + pow(msSize.y * (1 - mCenterY), 2.0f));
		Rad = GetAngle(msSize.x * (1 - mCenterX), msSize.y * (1 - mCenterY)) + mAngle;
		vx[RIGHTTOP] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uRight,vTop, msColor };

		//! 左上
		Hypotenuse = (float)sqrt(pow(msSize.x * mCenterX, 2.0f) + pow(msSize.y * (1 - mCenterY), 2.0f));
		Rad = PI - GetAngle(msSize.x * mCenterX, msSize.y * (1 - mCenterY)) + mAngle;
		vx[LEFTTOP] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uLeft,vTop, msColor };

		//! 左下
		Hypotenuse = (float)sqrt(pow(msSize.x * mCenterX, 2.0f) + pow(msSize.y * mCenterY, 2.0f));
		Rad = GetAngle(msSize.x * mCenterX, msSize.y * mCenterY) + PI + mAngle;
		vx[LEFTDOWN] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uLeft,vBottom, msColor };

		//! 右下
		Hypotenuse = (float)sqrt(pow(msSize.x * (1 - mCenterX), 2.0f) + pow(msSize.y * mCenterY, 2.0f));
		Rad = (PI * 2) - GetAngle(msSize.x * (1 - mCenterX), msSize.y * mCenterY) + mAngle;
		vx[RIGHTDOWN] = { msPos.x + (float)(cos(Rad) * Hypotenuse), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uRight,vBottom, msColor };

	}
	//! ポリゴン１
	vertex[0] = vx[LEFTTOP];     //! 左上
	vertex[1] = vx[RIGHTTOP];    //! 右上
	vertex[2] = vx[LEFTDOWN];    //! 左下
	//! ポリゴン２
	vertex[3] = vertex[1];       //! 右上
	vertex[4] = vx[RIGHTDOWN];   //! 右下
	vertex[5] = vertex[2];       //! 左下

	//! DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	//! 頂点のデータをVRAMに送る
	d3d->context->UpdateSubresource(mVertexBuffer,//! 転送先の頂点バッファ
		0, NULL, vertex,//! 転送する配列の名前（アドレス）
		0, 0);

	if (NoStopObj) {
		mAnimCnt++;
	}
	else if (GameMgr->GetAnimation()) {
		if (!StopAnimation) {
			mAnimCnt += 1; //! アニメーションカウントを進める
		}
	}
}


/*===================================================================================================================**
**  アニメーションに必要な情報のセッター　                                                                            *
**  引数 :  アニメーションテーブルの先頭のポインタ , アニメーションテーブルの要素数 , 横方向の分割数 ,縦方向の分割数　*
**===================================================================================================================*/
void AnimationSprite::SetAnimtionTable(int _xsplit, int _ysplit)
{

	//! サイズの計算
	float U = (1.0f / _xsplit);
	float V = (1.0f / _ysplit);
	//! UVサイズが違っていたら処理をする
	if (U != mSizeU || mSizeV != V) {

		//! サイズの計算
		mSizeU = U;
		mSizeV = V;


		//! 先に入っていたアニメーションテーブルを破棄する
		delete mpAnimTable;
		mpAnimTable = nullptr;

		//! アニメーションテーブルの要素数の設定
		mAnimTableElemnt = _xsplit + (_xsplit - 2);

		if (mAnimTableElemnt != 0) {
			//! アニメーションテーブルの生成
			mpAnimTable = new int[mAnimTableElemnt];

			//! アニメーションテーブルに値を設定　_xSplit-1番目まで
			for (int num = 0; num < _xsplit; num++) {
				mpAnimTable[num] = num;
			}

			//! アニメーションテーブルに値を設定　_XSpliti以降から最後まで
			int work = 1;
			for (int num = _xsplit; num < mAnimTableElemnt; num++) {
				mpAnimTable[num] = mpAnimTable[_xsplit - 1] - work;
				work++;
			}
		}

	}
}


/*====================================**
** アニメーションスピードのセッター    *
** 引数　アニメーションスピード 　　　 *
**====================================*/
void AnimationSprite::SetAnimSpeed(int _animspeed)
{
	mAnimSpeed = _animspeed;
}

/*===========================** 
** Y方向のコマ番号のセッター **
** 引数　Y方向のコマ番号     **
**===========================*/
void AnimationSprite::SetYSplit(int _ysplit)
{
	mYSplit = _ysplit;
}

/*===========================**
** X方向のコマ番号のセッター **
** 引数　X方向のコマ番号     **
**===========================*/
void AnimationSprite::SetXSplit(int _xsplit)
{
	//! 引数とIndexが同じになるまでアニメーションカウントを進める
	for (int i = 0; i < (mAnimTableElemnt * mAnimSpeed) + 32; i++) { //! ゲームが止まらないようにする
		int Index = (mAnimCnt / mAnimSpeed) % mAnimTableElemnt;
		if (mpAnimTable[Index] == _xsplit) {
			break;
		}
		else {
			mAnimCnt++;
		}
	}
}

//! アニメーションカウントのリセット関数
void AnimationSprite::ResetAnimCnt()
{
	mAnimCnt = 0;
}

void AnimationSprite::SetStopAnimation(bool _state)
{
	StopAnimation = _state;
}

void AnimationSprite::SetNoStopObj(bool _state)
{
	NoStopObj = _state;
}

int AnimationSprite::GetCurrentXSplit()
{
	return mCurrentXsplit;
}
