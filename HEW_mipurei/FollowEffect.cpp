#include "FollowEffect.h"
#include "Camerah.h"
#include "WinMain.h"
#include "Angle.h"

//! コンストラクタ
FollowEffect::FollowEffect(EffectInf _effect, eEffect _effectid, float & _x, float & _y)
	: x(_x), y(_y), Effect(_effect, _effectid)
{

}



//! 更新処理
void FollowEffect::Update()
{
	// アニメーションが最後まで行ったら
	if ((mSplit_y == msEffectInf.Split_y - 1) && (mSplit_x == msEffectInf.Split_x - 1)) {
		mEndflg = true;
	}
	//! ループフラグがたっていたらエフェクトを終わらないようにする
	if (Loop) {
		mEndflg = false;
	}


	VERTEX2D vx[4]; // 四頂点の位置	
	VERTEX2D vertex[6]; // 頂点の設定　バッファに送る用

	// 横方向に何番目のコマか計算する
	int Index = (mAnimFrameCnt / msEffectInf.AnimSpeed) % msEffectInf.Split_x; // アニメーションテーブルの添え字	
	mSplit_x = mpAnimTable[Index];

	//// 横方向の最後のコマまで来たら縦方向のコマ番号を下にずらす
	//if (mAnimFrameCnt == (msEffectInf.Split_x * msEffectInf.AnimSpeed) * (mSplit_y + 1)) {
	//	mSplit_y++;
	//}

	// UV座標を計算する
	float uLeft = mSize_u * mSplit_x;
	float uRight = uLeft + mSize_u;
	float vTop = mSize_v * mSplit_y;
	float vBottom = vTop + mSize_v;

	//CAMERA->EffectFix(x, y, mScale_x, mScale_y);
	//! 角度が設定されていたら
	if (mdAngle != 0) {
		// 中央を中心に回転
		double InitAngle = GetAngle(msEffectInf.mSize_x * mScale_x, msEffectInf.mSize_y * mScale_y);
		double LeftTopAngle = mdAngle + (DegreeToRadian(180) - InitAngle); // 左上頂点への角度 
		double RightTopAngle = mdAngle + InitAngle;
		double LeftDownAngle = RightTopAngle + PI;
		double RightDownAngle = LeftTopAngle + PI;

		vx[LEFTDOWN] = { (x + (float)(cos(LeftDownAngle) * mLength)), (y + (float)(sin(LeftDownAngle) * mLength)),uLeft,vBottom, mColor };
		vx[RIGHTDOWN] = { x + (float)(cos(RightDownAngle) * mLength), (y + (float)(sin(RightDownAngle) * mLength)),uRight,vBottom , mColor };
		vx[LEFTTOP] = { (x + (float)(cos(LeftTopAngle) * mLength)), (y + (float)(sin(LeftTopAngle) *mLength)),uLeft,vTop , mColor };
		vx[RIGHTTOP] = { (x + (float)(cos(RightTopAngle) * mLength)), (y + (float)(sin(RightTopAngle) * mLength)),uRight,vTop, mColor };
	}
	else {
		float left = x - msEffectInf.mSize_x * mScale_x / 2.0f;
		float right = x + msEffectInf.mSize_x * mScale_x / 2.0f;
		float top = y + msEffectInf.mSize_y * mScale_y / 2.0f;
		float bottom = y - msEffectInf.mSize_y * mScale_y / 2.0f;

		vx[LEFTDOWN] = { left,bottom,uLeft,vBottom,mColor };
		vx[RIGHTDOWN] = { right,bottom,uRight,vBottom,mColor };
		vx[LEFTTOP] = { left, top, uLeft, vTop, mColor };
		vx[RIGHTTOP] = { right,top,uRight,vTop,mColor };
	}
	// ポリゴン１
	vertex[0] = vx[LEFTTOP];     // 左上
	vertex[1] = vx[RIGHTTOP];    // 右上
	vertex[2] = vx[LEFTDOWN];    // 左下
	// ポリゴン２
	vertex[3] = vertex[1];       // 右上
	vertex[4] = vx[RIGHTDOWN];   // 右下
	vertex[5] = vertex[2];       // 左下

	// DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	// 頂点のデータをVRAMに送る
	d3d->context->UpdateSubresource(mVertexBuffer,//転送先の頂点バッファ
		0, NULL, vertex,//転送する配列の名前（アドレス）
		0, 0);

	mAnimFrameCnt++;
}
