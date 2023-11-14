#include "Collision.h"
#include <math.h>
#include <algorithm>
#include "Log.h"
#include "ObjTag.h"

//! �ǂ̕ӂ��ŏ��̒l�Ȃ̂����f���邽�߂̃}�N��
#define LEFT_MINIMUM 0
#define RIGHT_MINIMUM 1
#define TOP_MINIMUM 2
#define BOTTOM_MINIMUM 3


/*-------------------------------------------------------------------------------------------- - */
// �_�Ƌ�`�̓����蔻��֐�                                              //
// ����   : Shape�N���X , Box�N���X                                      //
// �߂�l : �������Ă��邩�ǂ���                                         //
bool Collision::Point_Box_Hit(Shape _pos1, Box _box2)
{	
	if (CheckActiv(_pos1, _box2)) {

		//! ��`�̊e�ӂɈʒu�����߂�
		float Left = _box2.GetVec().x - _box2.GetSize().x / 2;
		float Right = Left + _box2.GetSize().x;
		float Bottom = _box2.GetVec().y - _box2.GetSize().y / 2;
		float Top = Bottom + _box2.GetSize().y;


		//! �_����`���ɓ����Ă��邩�𔻒肷��
		if (Left <= _pos1.GetVec().x && Right >= _pos1.GetVec().x && Bottom <= _pos1.GetVec().y && Top >= _pos1.GetVec().y) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

/* --------------------------------------------------------------
// ��`�Ƌ�`�̓����蔻��                                      //
// �����@ : Box1, Box2                                         //
// �߂�l : �������Ă��邩�ǂ���                               */
bool Collision::Box_Box_Hit(Box _box1, Box _box2)
{
	if (CheckActiv(_box1, _box2)) {
		//! ��`1�̊e�ӂ����߂�
		float Left1 = _box1.GetLeft();
		float Right1 = _box1.GetRight();
		float Bottom1 = _box1.GetBottom();
		float Top1 = _box1.GetTop();

		//! ��`2�̊e�ӂɈʒu�����߂�
		float Left2 = _box2.GetLeft();
		float Right2 = _box2.GetRight();
		float Bottom2 = _box2.GetBottom();
		float Top2 = _box2.GetTop();

		return Right2 >= Left1 && Right1 >= Left2 && Top1 >= Bottom2 && Top2 >= Bottom1;
	}
	return false;
}

/* ------------------------------ 
// Map�̃A�C�e���Ƃ̓����蔻�� */
bool Collision::Box_MapItem(Box _box1, float _mapwidht, float _mapheight, Vector2 _pos)
{
	//! �Ώۂ̋�`�Ƃ̋����𒲂ׂ�
	_box1.GetSize();
	float dis = fabs(_box1.GetVec().x - _pos.x);                     //! ���S���W���狗��
	float HitDis = (_mapwidht / 2) + (_box1.GetSize().x / 2); //! ������\���̂��鋗�������_�̌덷���l�����ċ����͏����Z�߂ɂ���
	if (dis > HitDis) {
		return false;
	}

	if (_box1.GetActiv()) {
		//! ��`1�̊e�ӂ����߂�
		float Left1 = _box1.GetLeft();
		float Right1 = _box1.GetRight();
		float Bottom1 = _box1.GetBottom();
		float Top1 = _box1.GetTop();

		//! ��`2�̊e�ӂɈʒu�����߂�
		float Left2 = _pos.x - _mapwidht * 0.5f;
		float Right2 = Left2 + _mapwidht;
		float Bottom2 = _pos.y - _mapheight * 0.5f;
		float Top2 = Bottom2 + _mapheight;

		return Right2 >= Left1 && Right1 >= Left2 && Top1 >= Bottom2 && Top2 >= Bottom1;
	}

	return false;
}

//! �v���C���[�̐K���ƃ}�b�v�̃A�C�e���̓����蔻��ł�
bool Collision::Circle_MapItem(Circle _circle, float _width, float _hieght, Vector2 _pos)
{
	
	float Rad = _circle.GetRadiuse();     //! ���a�̎擾
	Vector2 CirclePos = _circle.GetVec(); //! �~�̈ʒu�̎擾
	//! �e�ӂ̎擾
	float Left = _pos.x - _width * 0.5f;
	float Right = Left + _width;
	float Top = _pos.y + _hieght * 0.5f;
	float Bottom = Top - _hieght;
	Truncation_Box(&Left, &Right, &Top, &Bottom); //! �����_�̐؂�̂�

	//! ������̗̈���v�Z����
	//! �c����
	float Region_Top = Top + Rad;
	float Region_Bottom = Bottom - Rad;
	//! ������
	float Region_Left = Left - Rad;
	float Region_Right = Right + Rad;

	//! �c���̗̈�Ƃ̓�����𔻒肷��
	if (Region_Top > CirclePos.y && Region_Bottom < CirclePos.y && Region_Left < CirclePos.x && Region_Right > CirclePos.x) {
		//! �e���_����ǂ̂��炢����Ă���̂����v�Z����
		float Rad2 = Rad * Rad; //! ���a��2��
		float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
		float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
		float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
		float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

		if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
			return true;
		}
	}	
	return false;
}


/* ------------------------------------------------------------
// �~�Ɖ~�̓����蔻��֐�                                    //
// ����   : Circle1, Circle2                                 //
// �߂�l : �������Ă��邩�ǂ���                             */
bool Collision::Circle_Circle_Hit(Circle _circle1, Circle _circle2)
{
	if (CheckActiv(_circle1, _circle2)) {

		//! ���S���W���m�̋������v�Z����
		float ptpx = _circle1.GetVec().x - _circle2.GetVec().x;
		float ptpy = _circle1.GetVec().y - _circle2.GetVec().y;
		float ptp = (ptpx * ptpx) + (ptpy * ptpy);
		//! ���a�P�Ɣ��a�Q�𑫂�������
		float h1h2 = _circle1.GetRadiuse() + _circle2.GetRadiuse();

		return h1h2 * h1h2 > ptp;
	}
	return false;
}



/* --------------------------------------------- 
// �����Ă�I�u�W�F�N�g���m�̓����蔻��       //
// ���� ��`�̏��A��`�̏��                */
bool Collision::Box_Box_Collision(Box & _box1, Box & _box2)
{
	//! �����蔻�肪�I���ɂȂ��Ă��邩�`�F�b�N����
	if (CheckActiv(_box1, _box2)) {

		//! �������̋����Ƃ�����\���̂��鋗���Ɣ�ׂ�
		//! ������\���̂��鋗������Ȃ�������false
		
		float Dis = fabs(_box1.GetVec().x - _box2.GetVec().x);
		float HitDis = (_box1.GetSize().x / 2) + (_box2.GetSize().x / 2);
		if (Dis > HitDis) {
			return false;
		}

		//! ���ꂼ��̍��W���擾
		Vector2 Vec_Box1 = _box1.GetVec();
		Vector2 Vec_Box2 = _box2.GetVec();

		//! ��`1�̊e�ӂ����߂�
		float CLeft = _box1.GetLeft();
		float CRight = _box1.GetRight();
		float CTop = _box1.GetTop();
		float CBottom = _box1.GetBottom();	
		Truncation_Box(&CLeft, &CRight, &CTop, &CBottom); //! �����_�ȉ��̐؂�̂�

		//! ��`2�̊e�ӂɈʒu�����߂�
		float Left = _box2.GetLeft();
		float Right = _box2.GetRight();
		float Bottom = _box2.GetBottom();
		float Top = _box2.GetTop();
		Truncation_Box(&Left, &Right, &Top, &Bottom); //! �؂�̂�

		if (Right >= CLeft && CRight >= Left && CTop >= Bottom && Top >= CBottom) {

			//! �����Ă�ʂ��擾
			Vector2 MoveVec_Box1 = _box1.GetMoveVec();
			Vector2 MoveVec_Box2 = _box2.GetMoveVec();
			Shape * point = _box1.Getthis();
			if (MoveVec_Box1 == 0.0f && MoveVec_Box2 == 0.0f) {
				StaticBox_StaticBox(_box1, _box2);								
			}
			//! Box1���������Ă��Ȃ���	
			else if (MoveVec_Box1 == 0.0f) {
				Box_StaticBox(_box2, _box1);
			}
			//! Box2�������Ă��Ȃ���
			else if (MoveVec_Box2 == 0.0f) {				
 				Box_StaticBox(_box1, _box2);
			}
			//! �ǂ���������Ă鎞
			else {		
				//! �C���������o��
				float FixTop =  Top - CBottom ; //! ��ւ̏C����
				float FixBottom = CTop - Bottom ; //! ���ւ̏C����
				float FixLeft = CRight - Left; //! ���ւ̏C����
				float FixRight = Right - CLeft; // ! �E�ւ̏C����

				//! �߂荞��ł���ʂ���Ԃ����Ȃ��������C������
				int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
				if (Minimum == LEFT_MINIMUM) { //! �������炠�����Ă���ꍇ
					//! �ǂ���������Ă���Ƃ�
					if (MoveVec_Box1.x != 0 && MoveVec_Box2.x != 0) {
						_box1.SetX(Vec_Box1.x - FixLeft / 2.0f);
						_box2.SetX(Vec_Box2.x + FixLeft / 2.0f);
					}
					//! Box1���������Ă�Ƃ�
					else if (MoveVec_Box1.x != 0 && MoveVec_Box2.x == 0) {
						_box1.SetX(Vec_Box1.x - FixLeft);
					}
					//! Box2�����������Ă鎞
					else {
						_box2.SetX(Vec_Box2.x + FixLeft);
					}
				}
				else if (Minimum == RIGHT_MINIMUM) { //! �E�����瓖�����Ă��鎞
					//! �ǂ���������Ă鎞
					if (MoveVec_Box1.x != 0 && MoveVec_Box2.x != 0) {
						_box1.SetX(Vec_Box1.x + FixRight / 2.0f);
						_box2.SetX(Vec_Box2.x - FixRight / 2.0f);
					}
					//! Box1���������Ă�Ƃ�
					else if (MoveVec_Box1.x != 0 && MoveVec_Box2.x == 0) {
						_box1.SetX(Vec_Box1.x + FixRight);
					}
					//! Box2���������Ă�Ƃ�
					else {
						_box2.SetX(Vec_Box2.x - FixRight);
					}
				}
				else if (Minimum == TOP_MINIMUM) { //! �ォ�瓖�����Ă���Ƃ�
					//! �ǂ���������Ă鎞
					if (MoveVec_Box1.y != 0 && MoveVec_Box2.y != 0) {
						_box1.SetY(Vec_Box1.y + FixTop / 2.0f);
						_box2.SetY(Vec_Box2.y - FixTop / 2.0f);					
					}
					//! Box1���������Ă�Ƃ�
					else if (MoveVec_Box1.y != 0 && MoveVec_Box2.y == 0) {
						_box1.SetY(Vec_Box1.y + FixTop);
					}
					//! Box2���������Ă�Ƃ�
					else {
						_box2.SetY(Vec_Box2.y - FixTop);
					}

					//! ��ɂ�����̃t���O�𗧂Ă�
					if (Vec_Box1.y > Vec_Box2.y) {
						_box1.SetOnObj(true);
					}
					else {
						_box2.SetOnObj(true);
					}
				}
				else if (Minimum == BOTTOM_MINIMUM) { //! �����瓖�����Ă鎞
					if (MoveVec_Box1.y != 0 && MoveVec_Box2.y != 0) {
						_box1.SetY(Vec_Box1.y - FixBottom / 2.0f);
						_box2.SetY(Vec_Box2.y + FixBottom / 2.0f);					
					}
					else if (MoveVec_Box1.y != 0 && MoveVec_Box2.y == 0) {
						_box1.SetY(Vec_Box1.y - FixBottom);
					}
					else {
						_box2.SetY(Vec_Box2.y + FixBottom);	
					}
					//! ��ɂ�����̃t���O�𗧂Ă�
					if (Vec_Box1.y > Vec_Box2.y) {
						_box1.SetOnObj(true);
					}
					else {
						_box2.SetOnObj(true);	
					}
				}				
			}
			//! �������Ă�����
			return true;
		}	
		return false;
	}
	return false;
}


/* ------------------------------------------------------ 
// ����������Ă��Ȃ���`�̓����蔻�菈��*/
void Collision::Box_StaticBox(Box & _box1, Box & _box2)
{
	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();
	//! �����_�ȉ��̐؂�̂�
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	//! ��`2�̊e�ӂɈʒu�����߂�
	float Left = _box2.GetLeft();
	float Right = _box2.GetRight();
	float Bottom = _box2.GetBottom();
	float Top = _box2.GetTop();
	//! �؂�̂�	
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! �e�����ւ̏C���ʂ�����
	float FixTop = Top - CBottom;          //! ��ւ̏C����
	float FixBottom = CTop - Bottom;       //! ���ւ̏C����
	float FixLeft = CRight - Left;         //! ���ւ̏C����
	float FixRight = Right - CLeft;        //! �E�ւ̏C����
	//! �C������ʂ���ԏ����������ɏC������
	int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
	if (Minimum == LEFT_MINIMUM) { //! �������炠�����Ă���ꍇ
		_box1.SetX(_box1.GetVec().x - FixLeft);
	}
	else if (Minimum == RIGHT_MINIMUM) { //! �E�����瓖�����Ă��鎞
		_box1.SetX(_box1.GetVec().x + FixRight);
	}
	else if (Minimum == TOP_MINIMUM) { //! �ォ�瓖�����Ă���Ƃ�
		//! ��Ɉړ����Ă�����C�����Ȃ�
		if (!(_box1.GetMoveVec().y >= 0.0f)) {
			_box1.SetY(_box1.GetVec().y + FixTop);
			_box1.SetOnObj(true);
		}       
	}
	else if (Minimum == BOTTOM_MINIMUM) { //! �����瓖�����Ă鎞
		_box1.SetY(_box1.GetVec().y - FixBottom);
	}	
}

/* ------------------------------------------- 
// �ǂ�����Î~���Ă����`�̓����蔻��֐� */
void Collision::StaticBox_StaticBox(Box & _box1, Box & _box2)
{
	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();
	//! �����_�ȉ��̐؂�̂�
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	float bx = floorf(_box2.GetVec().x * 1000) / 1000;
	float by = floorf(_box2.GetVec().y * 1000) / 1000;

	//! ��`2�̊e�ӂɈʒu�����߂�
	float Left = _box2.GetLeft();
	float Right = _box2.GetRight();
	float Bottom = _box2.GetBottom();
	float Top = _box2.GetTop();
	//! �؂�̂�	
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! �e�����ւ̏C���ʂ�����
	float FixTop = Top - CBottom;    //! ��ւ̏C����
	float FixBottom = CTop - Bottom; //! ���ւ̏C����
	float FixLeft = CRight - Left;   //! ���ւ̏C����
	float FixRight = Right - CLeft;  //! �E�ւ̏C����
	//! �C������ʂ���ԏ����������ɏC������

	int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);	
	if (Minimum == TOP_MINIMUM) { //! �ォ�瓖�����Ă���Ƃ�
		_box1.SetOnObj(true);			
	}
	else if (Minimum == BOTTOM_MINIMUM){
		_box2.SetOnObj(true);
	}
}
/* ------------------------------------------
// ��`�Ɖ~�̓����蔻������֐�          //
// ����   : ��` , �~                      //
// �߂�l : �������Ă��邩�ǂ���           */
bool Collision::Box_Circle_Hit(Box _Box, Circle _Circle)
{	
	float dis = fabs(_Box.GetVec().x - _Circle.GetVec().x);
	float HitDis = _Box.GetSize().x + _Circle.GetRadiuse();
	if (dis > HitDis) {
		return false;
	}

	if (CheckActiv(_Box, _Circle)) {
		float Rad = _Circle.GetRadiuse();     //! ���a�̎擾
		Vector2 CirclePos = _Circle.GetVec(); //! �~�̈ʒu�̎擾
		//! �e�ӂ̎擾
		float Left = _Box.GetLeft();
		float Right = _Box.GetRight();
		float Top = _Box.GetTop();
		float Bottom = _Box.GetBottom();
		Truncation_Box(&Left, &Right, &Top, &Bottom); //! �����_�̐؂�̂�

		//! ������̗̈���v�Z����
		//! �c����
		float Region_Top = Top + Rad;
		float Region_Bottom = Bottom - Rad;
		//! ������
		float Region_Left = Left - Rad;
		float Region_Right = Right + Rad;

		//! �c���̗̈�Ƃ̓�����𔻒肷��
		if ((Region_Top > CirclePos.y) && (Region_Bottom < CirclePos.y) && (Region_Left < CirclePos.x) && (Region_Right > CirclePos.x)) {
			//! �e���_����ǂ̂��炢����Ă���̂����v�Z����
			float Rad2 = Rad * Rad; //! ���a��2��
			float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
			float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
			float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
			float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

			if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
				return true;
			}
		}
	}
	return false;
}

/* -----------------------------------------
// ��`�Ɖ~�̋������͂���֐�             //
// ����   : ��`�Ɖ~�̒��S���W            //
// �߂�l : ����                          */
float Collision::DistanceBox_Circle(const float _BoxX, const float _BoxY, const float _CircleX, const float _CircleY)
{
	float dx = _CircleX - _BoxX;
	float dy = _CircleY - _BoxY;

	//2�悷��̂ŁA���K���̕K�v�Ȃ��H
	return (dx * dx) + (dy * dy);
}

/* ------------------------------------- 
// ������(�U����)�ƃ}�b�v�̓����蔻�� */
bool Collision::Tail_Map(Circle _circle, float _mapwidht, float _mapheight, Vector2 _pos)
{
	if (_circle.GetActiv()) {
		float Rad = _circle.GetRadiuse();
		Vector2 CirclePos = _circle.GetVec();
		float bx = floorf(_pos.x * 1000) / 1000;
		float by = floorf(_pos.y * 1000) / 1000;
		//! ��`2�̊e�ӂɈʒu�����߂�
		float Left = bx - (_mapwidht * 0.5f);
		float Right = Left + _mapwidht;
		float Bottom = by - (_mapheight * 0.5f);
		float Top = Bottom + _mapheight;
		//! �؂�̂�
		Truncation_Box(&Left, &Right, &Top, &Bottom);

		//! ������̗̈���v�Z����
		//! �c����
		float Region_Top = Top + Rad;
		float Region_Bottom = Bottom - Rad;
		//! ������
		float Region_Left = Left - Rad;
		float Region_Right = Right + Rad;

		//! �c���̗̈�Ƃ̓�����𔻒肷��
		if (Region_Top > CirclePos.y && Region_Bottom < CirclePos.y && Region_Left < CirclePos.x && Region_Right > CirclePos.x) {
			//! �e���_����ǂ̂��炢����Ă���̂����v�Z����
			float Rad2 = Rad * Rad; //! ���a��2��
			float LeftTop = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Top, 2);
			float RightTop = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Top, 2);
			float LeftBottom = powf(CirclePos.x - Left, 2) + powf(CirclePos.y - Bottom, 2);
			float RightBottom = powf(CirclePos.x - Right, 2) + powf(CirclePos.y - Bottom, 2);

			if (Rad2 < LeftTop || Rad2 < RightTop || Rad2 < RightBottom || Rad2 < LeftBottom) {
				return true;
			}
		}
	}
	return false;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------- */
// �}�b�v�p�̓����蔻��@(��`)�@�@�@�@�@�@�@�@�@�@�@�@                                                                                 �@�@�@//
// ���� : ��`�̃L�����̓����蔻���� , �}�b�v�`�b�v�̉���, �}�b�v�`�b�v�̗��� , �}�b�v�`�b�v�̈ʒu ,�@�e�ʂɑ΂��Ċ��ɓ������Ă��邩�̃t���O//
// �߂�l : �n�ʂɐG��Ă��邩
bool Collision::Box_BoxMap(Box & _box1, float _mapwidht, float _mapheight, Vector2 _pos)
{
	if (!_box1.GetActiv()) {
		return false;
	}

	bool TouchGround = false;

	//! �Ώۂ̋�`�Ƃ̋����𒲂ׂ�
	_box1.GetSize();
	float dis = fabs(_box1.GetVec().x - _pos.x);                     //! ���S���W���狗��
	float HitDis = (_mapwidht / 2) + (_box1.GetSize().x / 2); //! ������\���̂��鋗�������_�̌덷���l�����ċ����͏����Z�߂ɂ���
	if (dis >  HitDis) {
		return false;
	}

	float CLeft = _box1.GetLeft();
	float CRight = _box1.GetRight();
	float CTop = _box1.GetTop();
	float CBottom = _box1.GetBottom();

	//! �����_�ȉ��̐؂�̂�
	Truncation_Box(&CLeft, &CRight, &CTop, &CBottom);

	float bx = floorf(_pos.x * 1000) / 1000;
	float by = floorf(_pos.y * 1000) / 1000;

	//! ��`2�̊e�ӂɈʒu�����߂�
	float Left = bx - (_mapwidht * 0.5f);
	float Right = Left + _mapwidht;
	float Bottom = by - (_mapheight * 0.5f);
	float Top = Bottom + _mapheight;
	//! �؂�̂�
	Truncation_Box(&Left, &Right, &Top, &Bottom);

	//! �������Ă��邩�𔻒f����
	if (Right >= CLeft && CRight >= Left && CTop >= Bottom && Top >= CBottom) {
		//! �e�����ւ̏C���ʂ�����
		float FixTop = Top - CBottom;    //! ��ւ̏C����	    
		float FixBottom = CTop - Bottom; //! ���ւ̏C����
		float FixLeft = CRight - Left;   //! ���ւ̏C����
		float FixRight = Right - CLeft;  //! �E�ւ̏C����
		//! �C������ʂ���ԏ����������ɏC������
		int Minimum = GetMinimum(FixLeft, FixRight, FixTop, FixBottom);
		if (Minimum == LEFT_MINIMUM) { //! �������炠�����Ă���ꍇ
			_box1.SetX(_box1.GetVec().x - FixLeft);
		}
		else if (Minimum == RIGHT_MINIMUM) { //! �E�����瓖�����Ă��鎞
			_box1.SetX(_box1.GetVec().x + FixRight);
		}
		else if (Minimum == TOP_MINIMUM) { //! �ォ�瓖�����Ă���Ƃ�
			//! ��Ɉړ����Ă�����C�����Ȃ�
			if (!(_box1.GetMoveVec().y > 0.0f)) {
				TouchGround = true; //! �ォ�瓖����Ƃ��͒n�ʂɐG��Ă���
				_box1.SetY(_box1.GetVec().y + FixTop);
			}
		}
		else if (Minimum == BOTTOM_MINIMUM) { //! �����瓖�����Ă鎞
			_box1.SetY(_box1.GetVec().y - FixBottom);
		}
		
		return TouchGround;
	}

	return false;
}

//! ��`�p�̏����_�؂�̂Ċ֐�
void Collision::Truncation_Box(float * _left, float * _right, float * _top, float * _bottom)
{
	*_left = floorf(*_left * 1000) / 1000;
	*_right = floorf(*_right * 1000) / 1000;
	*_top = floorf(*_top * 1000) / 1000;
	*_bottom = floorf(*_bottom * 1000) / 1000;
}

/*-------------------------------------------------------------
// �����蔻��؂�ւ��p�t���O�̃`�F�b�N�֐�                  //
// ���� �`�F�b�N�������`��N���X1, �`�F�b�N�������`��N���X1 //
// �߂�l : �ǂ���������蔻�肪�I���ɂȂ��Ă����true��Ԃ� */
bool Collision::CheckActiv(Shape _shape1, Shape _shape2)
{
	if (_shape1.GetActiv() && _shape2.GetActiv()) {
		return  true;
	}
	return false;
}

/* -------------------------------------------------
// �����̒�����ǂꂪ�ŏ��Ȃ̂��������Ă����֐� */
int Collision::GetMinimum(float _left, float _right, float _top, float _bottom)
{
	float Array[4] = {_left, _right, _top, _bottom};
	int size = sizeof(Array) / sizeof(Array[0]);
	
	std::sort(Array,Array + size);
	
	if (Array[0] == _left) {
		return LEFT_MINIMUM;
	}
	else if (Array[0] == _right) {
		return RIGHT_MINIMUM;
	}
	else if (Array[0] == _top) {
		return TOP_MINIMUM;
	}	
	return BOTTOM_MINIMUM;
}