#pragma once
#include "BaseEnemy.h"

//! �h���[���̊�{�ƂȂ�N���X
class BaseDrone :
	public BaseEnemy
{
public:
	BaseDrone();	//! �R���X�g���N�^
	BaseDrone(float _x, float _y);		//! �R���X�g���N�^�Q
	~BaseDrone();						//! �f�X�g���N�^
	void Update();						//! �X�V����
	void Draw();						//! �`�揈��
	void SetEnemy(BaseEnemy* _EnemyNo);	//! �G�̃Z�b�^�[
	void EnemyBase();		//! ������Ă���G�̍s���i���̓h���[���ɒǏ]���邾���j
	void Fly();				//! �ړ��Ǝ��ۂ̍s���̏���
	bool GetCarryFlg();     //! �L�����[�t���O�̃Q�b�^�[
	TailReaction Reaction;	//! �h���ꂽ�����ۂ̔���
	TailReaction SetStingPower(float _Power, bool _Elect)override;	//! �h���ꂽ�����̃Z�b�^�[
	//! �t���O�֌W
	bool CarryFlg;	//! �G�������^��ł��邩�ǂ����̔��f
private:
	float TotalMove; //! �ړ�����
	float mfSpeed;   //! �X�s�[�h
	BaseEnemy * mcpEnemy;	//! ������Ă���G
};