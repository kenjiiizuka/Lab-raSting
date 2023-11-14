#pragma once
#include "AnimationHitObject.h"
class PlayerSmoke :
	public AnimationHitObject
{
public:
	PlayerSmoke();
	~PlayerSmoke();

	void Update();
	void Draw();

	void SmokeStart(Vector2 _pos);
	void SmokeStop();
private:
	
};

