#include "Circle.h"

Circle::Circle(Vector2 & _vec, float  _radiuse)
	: Shape(_vec)
{
	mRadiuse = _radiuse;
}

float Circle::GetRadiuse()
{
	return mRadiuse;
}

void Circle::SetRadiuse(float _radiuse)
{
	mRadiuse = _radiuse;
}
