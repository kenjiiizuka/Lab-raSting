#pragma once
#include "Dynamo.h"

//! ���₷�����d�@�ł�

class WeakDynamo :
	public Dynamo
{
public:
	WeakDynamo();
	
	void Update() override;
	TailReaction ReturnReaction(float _power, bool _elect) override; //! �h����Ă����ۂɃ��A�N�V������Ԃ�
	bool Overheat();                                    //! �I�[�o�[�q�[�g��������Ԃ�
	void SetChrage(bool _state);                        //! ���d�@�̃`���[�W���ꂽ���ǂ����̃Z�b�^�[
private:
	bool mBreak;    //! ����t���O
	bool mOverheat; //! �I�[�o�[�q�[�g�t���O �Ԃ��Ȃ������ǂ���
	bool mCoolDown; //! �I�[�o�[�q�[�g������N�[���_�E�����邽�߂̃t���O
	float g,b;      //! �O���[���@�u���[
};

