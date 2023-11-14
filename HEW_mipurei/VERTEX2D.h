#pragma once

// 頂点情報用の構造体ヘッダ

struct RGBA
{
	float r, g, b, a;

	RGBA();
	RGBA(float _r, float _g, float _b, float _a);
};

struct VERTEX2D{

	float x, y;
	float u, v;
	RGBA color;

	VERTEX2D();
	VERTEX2D(float _x,float _y,float _u, float _v, RGBA _color);

};

