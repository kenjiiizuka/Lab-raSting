#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle(Vector2 & _vec, float  _radiuse);
	float GetRadiuse();
	void SetRadiuse(float _radiuse);
private:
	float mRadiuse;
};

