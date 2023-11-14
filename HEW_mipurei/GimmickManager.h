#pragma once
#include <string>
#include "Character.h"
#include "Dynamo.h"
#include "BigDoor.h"
#include "CheckPoint.h"
#include "BreakObj.h"
#include "WeakDynamo.h"
#include "Goal.h"
#include "PressMachine.h"
#include <vector>
/* ------------------------------- 
// �M�~�b�N���Ǘ�����N���X�ł� */



class GimmickManager
{
public:
	GimmickManager(std::string _filename);  //! �R���X�g���N�^
	~GimmickManager();                      //! �f�X�g���N�^

	void Update();
	void CollisionUpdate(Character * _char);
	void Draw();
	void MoveX(float _x);      //! �S�ẴM�~�b�N��X�̈ʒu�����炷
	//! �`�F�b�N�|�C���g�P�͕��ʂ̒��ԁ@�Q���{�X�O�̒��Ԃ̗\��
	bool GetCheackPointState();               //! ���ʂ̒��ԃ|�C���g
	bool GetCheackPointBossState();           //! �{�X�O
	Vector2 GetCheackPointPos();              //! ���Ԃ̍��W�̃Q�b�^�[
	Vector2 GetCheackPointBossPos();          //! ���Ԃ̍��W�̃Q�b�^�[
	Goal * GetGoalIns();                      //! �S�[�����̂̎擾�@�{�X���ł�1-3�Ŏg��
	bool GetGoal();                           //! �S�[����������������

private:

	struct GimmickIndex
	{
		int Dynamo;
		int WeakDyanamo;
		int BigDoor;
		int Glass;
		int CheackPoint;
		int Press;
	};

	Vector2 CheackPos[2];            //! �`�F�b�N�|�C���g�̍��W�@�P�ڂ͕��ʂ̒��ԁ@��ڂ̓{�X�O����
	GimmickIndex Num;                //! �e�M�~�b�N�̐�
	Dynamo * mcpDynamo;              //! ���d�@
	WeakDynamo * mcpWeakDynamo;      //! ���锭�d�@
	BreakObj * mcpGlass;             //! �K���X
	BigDoor * mcpBigDoor;            //! �傫�ȃh�A
	CheackPoint * mcpCheackPoint;    //! ���Ԃۂ����
	PressMachine * mcpPress;            //! �v���X�@
	Goal * mcpGoal;                  //! �S�[��
	std::vector<Gimmick *> Gimmicks; //! �M�~�b�N�̔z��
	std::vector<Dynamo *> Dynamos;   //! ���d�@�̔z��
	int AllDyanmoIndex;              //! ���d�@�S�Ă̐�
};

