#pragma once
#include "GameObject.h"
#include "Box.h"
#include "Character.h"
class CheackBox :
	public GameObject
{
public:
	CheackBox(Vector2 _pos,Vector2 _size);
	~CheackBox();
	
	bool HitCheack(Character * object);
	void Collision(Character * obj);
private:
	Box * MyHit;

};

