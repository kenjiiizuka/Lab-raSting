#pragma once
#include "BaseScene.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void Update() override;
	void Draw() override;

private:
	// GameScene���Ŏg���֐��A�ϐ���錾���Ă�������
};

