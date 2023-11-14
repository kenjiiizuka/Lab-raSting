#pragma once
#include "BaseScene.h"
#include "EnemyManager.h"
#include "Map1_4.h"


class Stage1_4 :
	public BaseScene
{
public:
	Stage1_4();
	~Stage1_4();

	void Update();
	void Draw();

private:
	void CollisionUpdate();
	void ReSpawn();

	EnemyManager * mcpEnemyManager;
	Map1_4 * mcpMap;
	Player * mcpPlayer;
	bool mCheackPoint; //! ’†ŠÔ‚ÉG‚ê‚Ä‚¢‚é‚©‚Ìƒtƒ‰ƒO
	bool PlayBGM;  
};

