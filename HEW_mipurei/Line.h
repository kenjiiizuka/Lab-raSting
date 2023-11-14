#pragma once
#include "Shape.h"

/* ---------------------------
// ���̏������N���X�ł� */
//! ���g�̍��W�𒆐S�ɂ����A�����̐��ł�
class Line :
	public Shape
{
public:
	Line(Vector2 _pos, float _length, float _angle); //! �R���X�g���N�^

	float GetLength();
	void SetLength(float _length);
	float GetAngle();
	void SetAngle(float _angle);
	Vector2 GetLine_StartPos(); //! �����̎n�_�̃Q�b�^�[
	Vector2 GetLine_EndPos();   //! �����̏I�_�̃Q�b�^�[
	
private:
	float mLength;
	float mAngle;
};

