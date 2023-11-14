#pragma once
#include "Character.h"
class TestChar :
	public Character
{
public:
	TestChar();
	~TestChar();

	void Update();
	void Draw();
	void FixUpdate();

	//Box * GetBoxCol2();
private:
};

