#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "StageSelectMap.h"
//! ステージを選択して、

class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	void Update();
	void Draw();
	
private:
	bool CameraSeted; //! カメラをセットしたかどうか
	eScene OldStage;
	Player * mcpPlayer;
	StageSelectMap_1 * mcpMap;           //! 当たり判定
};

