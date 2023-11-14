#pragma once
#include "AnimationHitObject.h"
#include"Circle.h"
class ProtoAnimObj :
	public AnimationHitObject
{
public:
	ProtoAnimObj();
	~ProtoAnimObj();
	void Update()override;
	void Draw()override;
	Circle* GetmpCircle();
private:
	Circle* mpCircle;//‰~‚Æ‹éŒ`‚Ì“–‚½‚è”»’è‚ÌA‰~’S“–
};