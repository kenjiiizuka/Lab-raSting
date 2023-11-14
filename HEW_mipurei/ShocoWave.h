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
	Vector2 InitPos; //! ���̏Ռ��g�����������ꏊ
	Box * mcpBox;
	Vector2 ColPos; //! �����蔻��̍��W
	Vector2 ColSize;
	bool Act = false;
	bool TailHit = false;
	float Arufa = 0;
	float speed = 0.02f;
};

