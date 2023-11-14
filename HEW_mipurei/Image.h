#pragma once
#include "direct3d.h"


class Image
{
public:
	Image();
	~Image();
	// 静止画
	void DrawSprite(float _x, float _y, float _width, float _vertical, ID3D11ShaderResourceView* _Texture, float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); // 中心座標　縦横のサイズ,画像
	// チップ系　キャラチップなどの描画 
	void DrawDivSprite(float _x, float _y, float _width, float _vertical, int _Divx, int _Divy, int _Num, ID3D11ShaderResourceView* _Texture , float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); // 中心座標　縦横　分割数X、Y、何番目の画像,　画像

private:
	ID3D11Buffer* mVertexBuffer;    // このスプライトで使う頂点バッファ
	void Draw(ID3D11ShaderResourceView*, ID3D11Buffer*);	

};

