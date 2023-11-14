#include "NecthorHammer_InClass.h"

NecthorHammer::NecthorHammer()
{
	ColSize.x = 0.4f;
	ColSize.y = 0.4f;
	Col = new Box(Vec, ColSize.x, ColSize.y);
	AtkCol = new Box(Vec, ColSize.x, ColSize.y);
}

NecthorHammer::~NecthorHammer()
{
	delete Col;
	delete AtkCol;
}
