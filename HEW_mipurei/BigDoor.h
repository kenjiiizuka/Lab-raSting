#pragma once
#include "Gimmick.h"
#include"Box.h"
/*
�傫�ȃh�A�̃N���X�ł��B(�V���b�^�[�݂����ȓ����H)
����J�n���F2022/11/21
����ҁF����r��
*/

class BigDoor :
	public Gimmick
{
public:
	BigDoor();//�����ʒu�w�������R���X�g���N�^
	~BigDoor();
	void Update();
private:
	float mTotal; //! �ړ�������
	int mFrameCnt; //! �t���[���𐔂���
};

