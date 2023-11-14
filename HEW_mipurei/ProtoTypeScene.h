#pragma once
#include "BaseScene.h"
#include"GameObject.h"
#include"cMap.h"
#include"Necthor.h"
#include"Player.h"
#include"Map1_1.h"
#include"ProtoGoal.h"
#include"HPICon.h"
//====================================================//
/*
プロトタイプ版用のマップです。
作成者：仲野睦基
*/
//====================================================//
class PrototypeScene :
	public BaseScene
{
public:
	PrototypeScene();
	~PrototypeScene();
	void Update()override;
	void Draw()override;
private:
	Necthor* mpNecthor;//1面ボスのオブジェクト
	ProtoGoal* mpGoal;//ゴールオブジェクト
	Map1_1 *tmpPMap1_1;
	Player* tmpPlayer;//飯塚君の作ってるプレイヤーオブジェクト。(位置指定コンストラクタ)
	HPICon* mpIcon;//DX22の玉配列みたいな感じで横並びにする

	int TestHP = 5;//HPIconクラスの動作確認用変数。
};