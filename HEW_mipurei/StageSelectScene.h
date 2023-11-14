#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "StageSelectMap.h"
//! �X�e�[�W��I�����āA

class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	void Update();
	void Draw();
	
private:
	bool CameraSeted; //! �J�������Z�b�g�������ǂ���
	eScene OldStage;
	Player * mcpPlayer;
	StageSelectMap_1 * mcpMap;           //! �����蔻��
};

