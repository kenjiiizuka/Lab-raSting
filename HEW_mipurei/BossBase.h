#pragma once
#include "Character.h"
/*
�Q�[���ɓo�ꂷ��{�X�̊��N���X�ł��B�����h�������āA�{�X�{�̂����܂��B
����J�n���F2022/11/21
����ҁF����r��
*/
class BossBase :
	public Character
{
public:
	BossBase();
	~BossBase();
	virtual void Update();
	virtual void Draw();
};

