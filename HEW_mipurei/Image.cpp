#include "Image.h"
#include "VERTEX2D.h"
#include <Windows.h>

// コンストラクタ
Image::Image()
{
	//頂点バッファを作成
	HRESULT hr; //成功したかの結果を受け取る型
	DIRECT3D* d3d = Direct3D_Get();

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

	if (FAILED(hr))
	{
		// 頂点バッファの作成に失敗したときの処理をここに書く
		OutputDebugString((L"エラー発生！\n"));
	}
}


// デストラクタ
Image::~Image()
{
	COM_SAFE_RELEASE(mVertexBuffer);
}


/*=!静止画の描画!=============================================
===!引数 描画座標, 描画サイズ, テクスチャ, R, G, B, A(透明度)
============================================================*/
void Image::DrawSprite(float _x,float _y, float _width,float _vertical, ID3D11ShaderResourceView * _Texture, float _r, float _g, float _b, float _a)
{
	DIRECT3D* d3d = Direct3D_Get();

	RGBA color(_r, _g, _b, _a);
	// オブジェクトの中心から４頂点を計算する
	
	float xLeft = _x - _width / 2; //スプライトの左端X
	float xRight = _x + _width / 2; //スプライトの右端X
	float yTop = _y + _vertical / 2; //スプライトの上端Y
	float yBottom = _y - _vertical / 2; //スプライトの下端Y

	VERTEX2D vx[6];                         // 頂点情報
	// ポリゴンの頂点を決める(背景01)
	vx[0] = { xLeft,yTop, 0.0f, 0.0f, color };        // { x, y, u, v } 左上
	vx[1] = { xRight, yTop, 1.0f, 0.0f, color };      // 右上
	vx[2] = { xRight, yBottom, 1.0f, 1.0f, color };   // 右下
	vx[3] = vx[2];                                    // 右下
	vx[4] = { xLeft, yBottom, 0.0f, 1.0f, color };    // 左下
	vx[5] = vx[0];						              // 左上

	// 頂点のデータをVRAMに送る
	d3d->context->UpdateSubresource(mVertexBuffer,//転送先の頂点バッファ
		0, NULL, vx,//転送する配列の名前（アドレス）
		0, 0);

	Draw(_Texture, mVertexBuffer);
}


/*=!チップ状の画像を描画する=================================================================================
===!引数 描画座標, 描画サイズ, 横方向の分割数, 縦方向の分割数, 何番目なのか, テクスチャ,  R, G, B, A(透明度)
============================================================================================================*/
void Image::DrawDivSprite(float _x, float _y, float _width, float _vertical, int _Divx, int _Divy, int _Num, ID3D11ShaderResourceView * _Texture, float _r , float _g , float _b , float _a )
{
	DIRECT3D* d3d = Direct3D_Get();

	RGBA color(_r, _g, _b, _a);
	// オブジェクトの中心から４頂点を計算する
	float xLeft = _x - _width / 2;    // スプライトの左端X
	float xRight = _x + _width / 2;   // スプライトの右端X
	float yTop = _y + _vertical / 2;    // スプライトの上端Y
	float yBottom = _y - _vertical / 2; // スプライトの下端Y

	// １コマのサイズ
	float uvWidth = (1.0f / _Divx);  // Uの長さ
	float uvHeight = (1.0f / _Divy); // Vの長さ

	// 何番目の画像なのかを計算する
	int Numx = _Num % _Divx;
	int Numy = _Num / _Divx;

	float uLeft = Numx * uvWidth;    //左
	float uRight = uLeft + uvWidth;  //右
	float vTop = Numy * uvHeight;    //上
	float vBottom = vTop + uvHeight; //下

	VERTEX2D vertex[6];                         // 頂点情報
	// ポリゴンの頂点を決める(背景01)
	vertex[0] = { xLeft,yTop, uLeft, vTop,color };          // { x, y, u, v } 左上
	vertex[1] = { xRight, yTop, uRight, vTop,color };       // 右上
	vertex[2] = { xRight, yBottom, uRight, vBottom,color }; // 右下
	vertex[3] = vertex[2];                                  // 右下
	vertex[4] = { xLeft, yBottom, uLeft, vBottom ,color };  // 左下
	vertex[5] = vertex[0];						            // 左上

	// 頂点のデータをVRAMに送る
	d3d->context->UpdateSubresource(mVertexBuffer,//転送先の頂点バッファ
		0, NULL, vertex,//転送する配列の名前（アドレス）
		0, 0);

	Draw(_Texture, mVertexBuffer);
}



// 実際に描画する関数
void Image::Draw(ID3D11ShaderResourceView* _texture, ID3D11Buffer* _vertexBuffer)
{
	DIRECT3D* d3d = Direct3D_Get();

	// ポリゴン描画処理
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//ピクセルシェーダーにテクスチャをセットする
	d3d->context->PSSetShaderResources(0, 1, &_texture);

	// ピクセルシェーダーにサンプラーを渡す
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //ポイント保管

	//描画に使う頂点バッファの選択
	d3d->context->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	//描画命令
	d3d->context->Draw(6, 0);//第一引数＝頂点数
}

