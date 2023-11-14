#include "Effect.h"
#include "direct3d.h"
#include "VERTEX2D.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"
#include "Camerah.h"

// コンストラクタ
Effect::Effect(EffectInf _effect,eEffect _effectid)
{
	//頂点バッファを作成
	HRESULT hr; //成功したかの結果を受け取る型
	DIRECT3D* d3d = Direct3D_Get(); // まずDIRECT3D構造体にアクセス
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; // VRAMに確保するデータサイズ。通常は今から送る頂点データのサイズ。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 頂点バッファ作成をここで指定。
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// バッファ作成関数（デバイスクラスのメンバ関数）を呼び出し
	hr = d3d->device->CreateBuffer(&bufferDesc, NULL,
		&mVertexBuffer); //作った頂点バッファはここで指定した変数に保存される

	if (FAILED(hr)) {
		// 頂点バッファの作成に失敗したときの処理をここに書く
		OutputDebugString((L"エラー発生！\n"));
	}

	mEndflg = false;	
	mEffectID = _effectid;
	mAnimFrameCnt = 0;	
	mSplit_y = mSplit_x = 0;;	
	mColor = { 1.0f,1.0f,1.0f,1.0f };
	msEffectInf = _effect;
	mScale_x = mScale_y = 1.0f;
	mdAngle = _effect.Angle;
	// 描画サイズの計算
	mLength = sqrt((msEffectInf.mSize_x /2 * msEffectInf.mSize_x / 2) + (msEffectInf.mSize_y / 2 * msEffectInf.mSize_y / 2));

	// UVサイズの計算
	mSize_u = (1.0f / (float)msEffectInf.Split_x);
	mSize_v = (1.0f / (float)msEffectInf.Split_y);

	// アニメーションテーブルを生成
	mpAnimTable = new int[msEffectInf.Split_x];
	for (int num = 0; num < msEffectInf.Split_x; num++) {
		mpAnimTable[num] = num;
	}
}


// デストラクタ
Effect::~Effect()
{
	delete[] mpAnimTable;
	COM_SAFE_RELEASE(mVertexBuffer);
}


// エフェクトの更新処理 
void Effect::Update()
{	
	// アニメーションが最後まで行ったら
	if ((mSplit_y == msEffectInf.Split_y -1) && (mSplit_x == msEffectInf.Split_x - 1)) {
		mEndflg = true;
	}

	VERTEX2D vx[4]; // 四頂点の位置	
	VERTEX2D vertex[6]; // 頂点の設定　バッファに送る用

	// 横方向に何番目のコマか計算する
	int Index = (mAnimFrameCnt / msEffectInf.AnimSpeed) % msEffectInf.Split_x; // アニメーションテーブルの添え字	
	mSplit_x = mpAnimTable[Index];
	
	// 横方向の最後のコマまで来たら縦方向のコマ番号を下にずらす
	if (mAnimFrameCnt == (msEffectInf.Split_x * msEffectInf.AnimSpeed) * (mSplit_y + 1)) {
		mSplit_y++;
	}

	// UV座標を計算する
	float uLeft = mSize_u * mSplit_x;
	float uRight = uLeft + mSize_u;
	float vTop = mSize_v * mSplit_y;
	float vBottom = vTop + mSize_v;
	
	CAMERA->EffectFix(msEffectInf.pos_x,msEffectInf.pos_y,mScale_x,mScale_y);
	//! 角度が設定されていたら
	if (mdAngle != 0) {

		// 中央を中心に回転
		double InitAngle = GetAngle(msEffectInf.mSize_x * mScale_x, msEffectInf.mSize_y * mScale_y);
		double LeftTopAngle = mdAngle + (DegreeToRadian(180) - InitAngle); // 左上頂点への角度 
		double RightTopAngle = mdAngle + InitAngle;
		double LeftDownAngle = RightTopAngle + PI;
		double RightDownAngle = LeftTopAngle + PI;

		vx[LEFTDOWN] = { (msEffectInf.pos_x + (float)(cos(LeftDownAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(LeftDownAngle) * mLength)),uLeft,vBottom, mColor };
		vx[RIGHTDOWN] = { msEffectInf.pos_x + (float)(cos(RightDownAngle) * mLength), (msEffectInf.pos_y + (float)(sin(RightDownAngle) * mLength)),uRight,vBottom , mColor };
		vx[LEFTTOP] = { (msEffectInf.pos_x + (float)(cos(LeftTopAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(LeftTopAngle) *mLength)),uLeft,vTop , mColor };
		vx[RIGHTTOP] = { (msEffectInf.pos_x + (float)(cos(RightTopAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(RightTopAngle) * mLength)),uRight,vTop, mColor };
	}
	else {
		float left = msEffectInf.pos_x - msEffectInf.mSize_x * mScale_x / 2.0f;
		float right = msEffectInf.pos_x + msEffectInf.mSize_x * mScale_x / 2.0f;
		float top = msEffectInf.pos_y + msEffectInf.mSize_y * mScale_y / 2.0f;
		float bottom = msEffectInf.pos_y - msEffectInf.mSize_y * mScale_y / 2.0f;

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


// エフェクトの描画処理
void Effect::Draw()
{
	//DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();

	// ポリゴン描画処理
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//ピクセルシェーダーにテクスチャをセットする
	d3d->context->PSSetShaderResources(0, 1, &msEffectInf.mTexture);

	// ピクセルシェーダーにサンプラーを渡す
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //ポイント保管

	//描画に使う頂点バッファの選択
	d3d->context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//描画命令
	d3d->context->Draw(NUM_VERTEX, 0);//第一引数＝頂点数
}

void Effect::SetPos(float _x, float _y)
{
	//! 座標のセット
	msEffectInf.pos_x = _x;
	msEffectInf.pos_x = _y;
}

//! このエフェクトが終了したか判断するフラグを返す
bool Effect::GetEndFlg()
{
	return mEndflg;
}

eEffect Effect::GetEffectID()
{
	return mEffectID;
}
