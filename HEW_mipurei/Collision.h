#pragma once
#include "FLOAT2.h"
#include "Box.h"
#include "Circle.h"
#include "Vector2.h"
#include "Character.h"
//------------------------------------------------------
// �����蔻��N���X�i���j�����������ȂǂɎg���悤�ł�
// ����� : �ђ� ���i


#define PBH(_point, _box, _hit)  _hit = Collision::Point_Box_Hit(_point, _box)
#define BBC(_box1, _box2)        Collision::Box_Box_Collision(_box1,_box2) 
#define BBH(_box1, _box2)       Collision::Box_Box_Hit(_box1, _box2)
#define BCH(_box, _circle)      Collision::Box_Circle_Hit(_box, _circle)


class Collision
{
public:
	static bool Point_Box_Hit(Shape _box1, Box _box2);                         //! �_�Ƌ�`�̓����蔻������֐�
	static bool Box_Box_Hit(Box _box1, Box _box2);                             //! ��`�Ƌ�`�̓����蔻��
	static bool Box_MapItem(Box _box1, float _mapwidht, float _mapheight, Vector2 _pos);
	static bool Circle_MapItem(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos);
	static bool Circle_Circle_Hit(Circle _circle1, Circle _circle2);           //! �~�Ɖ~�̓����蔻��  ����m�F���Ă��܂���
	static bool Box_Box_Collision(Box & _box1, Box & _box2);                   //! ��`�̃I�u�W�F�N�g�̓����蔻�� (�����Ă�I�u�W�F�N�g)
	//static bool BoxChar_BoxChar(Character & _charbox1, Character & _chrabox2); //! ��`�̃L�������m�̓����蔻��
	static bool Box_Circle_Hit(Box _Box, Circle _Circle);                        //! �~�Ƌ�`�̓����蔻��
	static float DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY);//�����̑���

	//! MAP�p�̓����蔻��ł�
	static bool Tail_Map(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos);  //! �}�b�v�Ƃ����ۂ̓����蔻��
	static bool Box_BoxMap(Box & _box1, float _mapwidht, float _mapheight, Vector2 _pos);    //! ��`�̃L�����Ƌ�`�̓����蔻��@�����P�������Q�ɂ߂荞��ł�ʂ�Ԃ��Ă����
	//! �����_�̐؂�̂�
	static void  Truncation_Box(float * _left, float * _right, float * _top, float * _bottom);

private:
	static void Box_StaticBox(Box & _box1, Box & _box2);  //! �����Q�������ĂȂ��Ƃ��̋�`�̏Փ˔���֐�
	static void StaticBox_StaticBox(Box & _box1, Box & _box2); //! �ǂ�����Î~���Ă����`�̏Փ˔���֐�
	static bool CheckActiv(Shape _shape1, Shape _shape2); //! �����蔻��؂�ւ��悤�t���O�̃`�F�b�N�֐�
	static int GetMinimum(float _left, float _right , float _top, float _bottom); //! ��`�̓����蔻��̉��������Ŏg�������̒�����ŏ���Ԃ��֐�
};



