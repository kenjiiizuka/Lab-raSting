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
	// GameScene内で使う関数、変数を宣言してください
};

