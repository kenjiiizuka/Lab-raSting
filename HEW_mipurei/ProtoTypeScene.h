#pragma once
#include "BaseScene.h"
#include"GameObject.h"
#include"cMap.h"
#include"Necthor.h"
#include"Player.h"
#include"Map1_1.h"
#include"ProtoGoal.h"
#include"HPICon.h"
//====================================================//
/*
�v���g�^�C�v�ŗp�̃}�b�v�ł��B
�쐬�ҁF����r��
*/
//====================================================//
class PrototypeScene :
	public BaseScene
{
public:
	PrototypeScene();
	~PrototypeScene();
	void Update()override;
	void Draw()override;
private:
	Necthor* mpNecthor;//1�ʃ{�X�̃I�u�W�F�N�g
	ProtoGoal* mpGoal;//�S�[���I�u�W�F�N�g
	Map1_1 *tmpPMap1_1;
	Player* tmpPlayer;//�ђˌN�̍���Ă�v���C���[�I�u�W�F�N�g�B(�ʒu�w��R���X�g���N�^)
	HPICon* mpIcon;//DX22�̋ʔz��݂����Ȋ����ŉ����тɂ���

	int TestHP = 5;//HPIcon�N���X�̓���m�F�p�ϐ��B
};