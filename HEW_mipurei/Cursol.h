#pragma once
#include "AnimationHitObject.h"

//! �J�[�\���N���X
class Cursol :
	public AnimationHitObject
{
public:
	Cursol();
	~Cursol();

	void Update();
	Vector2 GetSelectPos(); //! ����{�^��������������Ԃ�
	Shape * GetShape();     //! ���g�̍��W
	bool Select();          //! ����{�^������������
};

