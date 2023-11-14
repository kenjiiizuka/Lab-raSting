#include "Sprite.h"
#include "direct3d.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"


//! コンストラクタ
Sprite::Sprite(Vector2 & _pos) : msPos(_pos)
{
	//! 頂点バッファを作成
	HRESULT hr;                             
	DIRECT3D* d3d = Direct3D_Get();              //! DIRECT3D構造体にアクセス
	D3D11_BUFFER_DESC bufferDesc;                
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; //! VRAMに確保するデータサイズ。通常は今から送る頂点データのサイズ。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //! 頂点バッファ作成をここで指定。
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// バッファ作成関数（デバイスクラスのメンバ関数）を呼び出し
	hr = d3d->device->CreateBuffer(&bufferDesc, NULL,
		&mVertexBuffer); //作った頂点バッファはここで指定した変数に保存される

	if (FAILED(hr))	{
		// 頂点バッファの作成に失敗したときの処理をここに書く
		OutputDebugString((L"エラー発生！\n"));
	}

	mPosU = mPosV = 0.5f;
	mSizeU = mSizeV = 1.0f;
	mAngle = 0;
	msColor = {1.0f,1.0f,1.0f,1.0f};
	mCenterX = mCenterY = 0.5f;
	mTexture = NULL;
	SplitDraw = false;
}

//! デストラクタ
Sprite::~Sprite()
{
	COM_SAFE_RELEASE(mVertexBuffer);
}

//! 更新処理
void Sprite::Update()
{	
	VERTEX2D vx[4]; //! 四頂点の位置

	//! 頂点の設定　バッファに送る用
	VERTEX2D vertex[6];

	float uLeft;
	float uRight;
	float vTop;
	float vBottom;
	//! テクスチャ上の座標を求める
	if(SplitDraw){
		// １コマのサイズ
		float uvWidth = (1.0f / XSplit);  // Uの長さ
		float uvHeight = (1.0f / YSplit); // Vの長さ

		// 何番目の画像なのかを計算する
		int Numx = TexNum % XSplit;
		int Numy = TexNum / XSplit;

		uLeft = Numx * uvWidth;    //左
		uRight = uLeft + uvWidth;  //右
		vTop = Numy * uvHeight;    //上
		vBottom = vTop + uvHeight; //下
	}
	else {
		uLeft = mPosU - (mSizeU / 2);
		uRight = mPosU + (mSizeU / 2);
		vTop = mPosV - (mSizeV / 2);
		vBottom = mPosV + (mSizeV / 2);
	}


	//! 角度が設定いない場合
	if (mAngle == 0.0f) {
		vx[LEFTDOWN] = { msPos.x - msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uLeft,vBottom, msColor};
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
		0, NULL, vertex, //! 転送する配列の名前（アドレス）
		0, 0);

}

//! 描画処理
void Sprite::Draw()
{
	//! DIRECT3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();

	//! ポリゴン描画処理
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//! ピクセルシェーダーにテクスチャをセットする
	d3d->context->PSSetShaderResources(0, 1, &mTexture);

	//! ピクセルシェーダーにサンプラーを渡す
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //ポイント保管

	//! 描画に使う頂点バッファの選択
	d3d->context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//! 描画命令
	d3d->context->Draw(NUM_VERTEX, 0);//第一引数＝頂点数

}

//! テクスチャのセッター
void Sprite::SetTexture(ID3D11ShaderResourceView * _texture)
{
	mTexture = _texture;
}

//! このスプライトのサイズのセッター 
void Sprite::SetSize(float _width, float _vertical)
{
	msSize.x = _width;
	msSize.y = _vertical;
}


//! 描画情報のセッター　UV座標、UVサイズ
void Sprite::SetUVSpriteInf(int _num, int _xsplit, int _ysplit, bool _state)
{
	TexNum = _num;
	XSplit = _xsplit;
	YSplit = _ysplit;
	SplitDraw = _state;
}

//! 角度のセッター
void Sprite::SetAngle(double _angle, float _centerx, float _centery)
{
	mAngle = _angle;
	mCenterX = _centerx;
	mCenterY = _centery;
}

//! 色情報のセッター
void Sprite::SetColor(float _r, float _g, float _b)
{
	msColor.r = _r;
	msColor.g = _g;
	msColor.b = _b;

}

//! 透明度のセッター
void Sprite::SetArufa(float _a)
{
	msColor.a = _a;
}





