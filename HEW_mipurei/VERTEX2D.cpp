#include "VERTEX2D.h"

VERTEX2D::VERTEX2D()
{
	x = 0;
	y = 0;
	u = 0;
	v = 0;
	color;
}

VERTEX2D::VERTEX2D(float _x, float _y, float _u, float _v , RGBA _color)
{	
	x = _x;
	y = _y;
	u = _u;
	v = _v;
	color = _color;
}

RGBA::RGBA()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}

RGBA::RGBA(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}
