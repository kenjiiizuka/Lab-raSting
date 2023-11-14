#pragma once
#include "AnimationHitObject.h"
#include"Box.h"
class ProtoGoal :
	public AnimationHitObject
	/*
	����ҁF����r��
	�S�[���n�_�̃N���X�ł��B
	�S�[�������t���O�̃Q�b�^�[�������Ă���A����ŃS�[���������Ƃ����m�����܂��B
	*/
{
public:
	ProtoGoal();
	ProtoGoal(float _X, float _Y);
	~ProtoGoal();
	void Update();
	void Draw();
	Box* GetmpGoalBox();
	//�����蔻��1��ڂ��擾����t���O
	bool GetFirstStabFlg();
	void SetFirstStabFlg(bool _Flg);
	//�����蔻��2��ڂ��擾����t���O
	bool GetSecondStabFlg();
	void SetSecondStabFlg(bool _Flg);
private:
	ID3D11ShaderResourceView * GoalTex;
	//�����蔻��m�F�p�摜
	Image mcImage;
	//�S�[���̓����蔻��
	Box* mpGoalCollisionBox;
	Vector2 GoalColiPos;
	//�ŏ��ɃS�[���Ƀv���O��˂��h�������������t���O
	bool FirstStabFlg;
	//2��ڂɐ����悭�v���O��˂��h�������������t���O
	bool SecondStabFlg;
};