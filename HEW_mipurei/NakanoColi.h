#pragma once
#include"Box.h"
#include"Circle.h"
/*
//����ҁF����r��
//�~�Ƌ�`�̓����蔻�������Ă܂�(11��12�����_)
//����������AColision�N���X�ɂ������Ă��������B���肢���܂��B
*/
class NakanoColi
{
public:
	static bool Box_Circle(Box* _Box,Circle* _Circle);//�~�Ƌ�`�̓����蔻��
	static float DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY);//�����̑���
};