#include "DrawValue.h"
#include "TextureManager.h"

//! コンストラクタ
DrawValue::DrawValue()
{
	mcpImage = new Image();
	//! テクスチャの読み込み
	LoadTexture(L"assets/Number/0.png", &ValueGraph[0]);
	LoadTexture(L"assets/Number/1.png", &ValueGraph[1]);
	LoadTexture(L"assets/Number/2.png", &ValueGraph[2]);
	LoadTexture(L"assets/Number/3.png", &ValueGraph[3]);
	LoadTexture(L"assets/Number/4.png", &ValueGraph[4]);
	LoadTexture(L"assets/Number/5.png", &ValueGraph[5]);
	LoadTexture(L"assets/Number/6.png", &ValueGraph[6]);
	LoadTexture(L"assets/Number/7.png", &ValueGraph[7]);
	LoadTexture(L"assets/Number/8.png", &ValueGraph[8]);
	LoadTexture(L"assets/Number/9.png", &ValueGraph[9]);
	LoadTexture(L"assets/Number/decimal.png", &Decimal);
	LoadTexture(L"assets/Number/minus.png", &Minus);
}

//! デストラクタ
DrawValue::~DrawValue()
{
	delete mcpImage;

	//! テクスチャの解放
	for (int num = 0; num < 10; num++) {
		COM_SAFE_RELEASE(ValueGraph[num]);
	}
	COM_SAFE_RELEASE(Decimal);
	COM_SAFE_RELEASE(Minus);
}
