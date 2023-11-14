#pragma once
#include "BaseScene.h"
#include "Map1_3.h"
#include "EnemyManager.h"
#include "ReNecthor.h"
#include "CheackBox.h"

class Stage1_3 :
	public BaseScene
{
public:
	Stage1_3();
	~Stage1_3();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! ���X�|�[���֐�(���g���C�������Ƃ��ɃX�e�[�W��v���C���[�A�G�l�~�[�����Z�b�g����֐�)
	void ReSpawn();
	bool BossCamera;  //! �{�X�悤�ɃJ�����̈ʒu���Œ�
	bool BossBattleStart; 
	Player * mcpPlayer;
	Map1_3 * mcpMap;
	ReNecthor * mcpNecthor;
	EnemyManager * mcpEnemyManager;
	CheackBox * Box01;                  //! �l�N�g�[���̌��ɂ��������Ȃ���
	//! �`���[�g���A������n�܂邩�A1-1����n�܂邩�ʂ��̂ł���𔻒f����t���O���K�v
	bool mCheackPoint; //! ���ԂɐG��Ă��邩�̃t���O
	bool mCheackPointBoss; //! �{�X�O����
	bool PlayBGM;  
};

