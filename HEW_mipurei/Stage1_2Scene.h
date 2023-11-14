#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map1_2.h"

class Stage1_2 :
	public BaseScene
{
public:
	Stage1_2();
	~Stage1_2();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! ���X�|�[���֐�(���g���C�������Ƃ��ɃX�e�[�W��v���C���[�A�G�l�~�[�����Z�b�g����֐�)
	void ReSpawn();

	Player * mcpPlayer;
	Map1_2 * mcpMap;
	EnemyManager * mcpEnemyManager;
	
	bool mCheackPoint; //! ���ԂɐG��Ă��邩�̃t���O
	bool PlayBGM;     
};

