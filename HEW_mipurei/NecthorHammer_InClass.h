#pragma once
#include "Box.h"

//! �{�X�̃n���}�[ �C���N���X�ł�
class NecthorHammer
{
public:
	NecthorHammer();
	~NecthorHammer();

	Box * Col;    //! �Փ˔���p
	Box * AtkCol; //! �U������p�̓����蔻��
	Vector2 Vec;
	Vector2 ColSize;
	bool TailHited = false;
	int Cnt = 0;
	bool Slamed = false;
};

