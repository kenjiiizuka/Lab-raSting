#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

class ShockWave :
	public AnimationHitObject
{
public:
	ShockWave();
	~ShockWave();
	void Update();
	void Draw();
	void ShockWaveStart(Vector2 _pos);
	void SetHit(bool hit);
	Box * GetCol();
private:
	Vector2 InitPos; //! この衝撃波が発生した場所
	Box * mcpBox;
	Vector2 ColPos; //! 当たり判定の座標
	Vector2 ColSize;
	bool Act = false;
	bool TailHit = false;
	float Arufa = 0;
	float speed = 0.02f;
};

