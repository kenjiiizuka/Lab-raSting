#pragma once
#include "BaseScene.h"
#include "Map1_5.h"
#include "EnemyManager.h"
#include "Necthor1_5.h"
#include "StageDoor.h"
#include "CheackBox.h"

class Stage1_5 :
	public BaseScene
{
public:
	Stage1_5();
	~Stage1_5();

	void Update();
	void Draw();

private:
	void CollisionUpdate();
	void ReSpawn();
	void Ending(); //! �G���f�B���O�悤�̏����@�����o�Ă���
	bool mBossBgmStart;

	EnemyManager * mcpEnemyManager;
	Map1_5 * mcpMap;
	Player * mcpPlayer;
	Necthor1_5 * mcpNecthor;
	CheackBox *  Box01;
	StageDoor * EndDoor;
	float DoorArufa;

	bool mCheackPoint; //! ���ԂɐG��Ă��邩�̃t���O
	bool mBossCheackPoint;
	bool BossCamera;  //! �{�X�悤�ɃJ�����̈ʒu���Œ�
	bool BossBattleStart;
	bool EndingFlg = false;
	bool PlayBGM;
};

