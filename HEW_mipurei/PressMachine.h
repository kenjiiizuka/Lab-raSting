#pragma once
#include "Gimmick.h"
class PressMachine :
	public Gimmick
{
public:
	PressMachine();
	~PressMachine();

	void Update();
	void Draw();
	Box * GetBoxCol() override;
private:
	Box * mBoxCol;
	Vector2 ColPos;
	Vector2 mColSize;

	bool Stop;
	int StopCnt;

	bool Sound = true;;
};

