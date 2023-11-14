#pragma once
#include "BaseScene.h"
#include "Map1_1.h"
#include "Player.h"
#include "EnemyManager.h"
#include "DrawMovei.h"
#include "CheackBox.h"
#include "BreakObj.h"
#include "BigDoor.h"
#include "Dynamo.h"

//! 1-1�V�[���ł�

class Stage1_1 :
	public BaseScene
{
public:
	Stage1_1();
	~Stage1_1();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! ���X�|�[���֐�(���g���C�������Ƃ��ɃX�e�[�W��v���C���[�A�G�l�~�[�����Z�b�g����֐�)
	void ReSpawn();
	bool ThoutrialMovie;
	Player * mcpPlayer;
	Map1_1 * mcpMap;
	EnemyManager * mcpEnemyManager;

	//! �`���[�g���A���ɕK�v�Ȃ���
	CheackBox * Cheak01;
	CheackBox * Cheak02;
	CheackBox * Cheak03;	
	DrawMovei * Movei01; //! �`���[�g���A�����[�r�[
	DrawMovei * Movei02; //! �`���[�g���A�����[�r�[
	DrawMovei * Movei03; //! �`���[�g���A�����[�r�[
	NormalEnemy * Timpiller01;
	BreakObj * Glass01;
	Dynamo * Dynamo01;
	BigDoor * Door01;


	//! �������p�̃t���O
	bool Glass_Success = true;
	bool Timpiller_Succes = true;
	bool Dynamo_Success = true;

	//! �`���[�g���A������n�܂邩�A1-1����n�܂邩�ʂ��̂ł���𔻒f����t���O���K�v
	bool mCheackPoint; //! ���ԂɐG��Ă��邩�̃t���O
	bool OnCamera;
	bool PlayBGM;

};

