#pragma once
#include "Character.h"
#include "PlugTail.h"
#include "HitStop.h"

class EnemyProt :
	public Character
{
public:
	EnemyProt();   //! �R���X�g���N�^�@�G�̃X�e�[�^�X���t�@�C������ǂݍ���Œ����ł���悤�ɂ���
	EnemyProt(float _x, float _y); //! �R���X�g���N�^�@���W�ݒ�\
	~EnemyProt();	//! �f�X�g���N�^
	void Update() override;
	void Draw() override;
	void Move();
private:
	HitStop * mcpHitStop;
	float MoveDis;
	bool LiveFlg;
	bool MoveDirFlg;
	bool GetAttack;
};