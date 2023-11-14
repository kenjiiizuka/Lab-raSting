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
	// GameScene“à‚Åg‚¤ŠÖ”A•Ï”‚ğéŒ¾‚µ‚Ä‚­‚¾‚³‚¢
};

