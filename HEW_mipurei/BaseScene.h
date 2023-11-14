#pragma once
#include "Image.h"
#include "eScene.h"
// 各シーンクラスの基底クラス

class BaseScene
{
public:
	BaseScene(){}
	virtual ~BaseScene(){}
	virtual void Update() {}
	virtual void Draw(){}
protected:
	Image * mcpImage; // 描画クラスです。静止画など、を描画する際につかって下さい。タイトルの背景など
	eScene Tag = Scene_None;

	bool BGM = true; //! BGM再生可能か
};

