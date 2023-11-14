#pragma once
#include "BaseScene.h"
#include "DrawMovei.h"

//! �G���f�B���O�V�[���ł�

class EndingScene :
	public BaseScene
{
public:
	EndingScene();
	~EndingScene();

	void Update();
	void Draw();
private:
	DrawMovei * EndingMovie;
	bool PlayBGM; 

	int FrameCnt;
};

