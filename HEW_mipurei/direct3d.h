#pragma once
#include <d3d11.h>

//解放用のマクロ
#define COM_SAFE_RELEASE(o) if(o!=NULL){o->Release();o=NULL;}

//Direct3d関係の変数をまとめる構造体

struct DIRECT3D
{
	ID3D11Device* device;					//デバイス
	ID3D11DeviceContext* context;			//コンテキスト
	IDXGISwapChain* swapChain;				//スワップチェイン
	ID3D11RenderTargetView* renderTarget;	//レンダーターゲット
	ID3D11VertexShader* vertexShader;       //頂点シェーダー
	ID3D11PixelShader* pixelShader;         //ピクセルシェーダー
	ID3D11InputLayout* inputLayout;         //インプットレイアウト
	ID3D11BlendState* blendAlpha;           //アルファブレンディング用ブレンドステート
	ID3D11SamplerState* samplerPoint;
};


/*========================*
  *****プロトタイプ宣言****
==========================*/
//Direct3Dの初期化を行う関数
BOOL Direct3D_Init(HWND hWnd);

//DIRECT3Dの解放を行う関数
void Direct3D_Release();

//DIRECT3D構造体の実態のアドレスを返す関数
DIRECT3D* Direct3D_Get();