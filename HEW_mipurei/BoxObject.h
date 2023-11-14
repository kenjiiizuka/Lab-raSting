#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
class BoxObject :
	public AnimationHitObject
{
public:
	BoxObject();                   //! �R���X�g���N�^
	BoxObject(float _x, float _y); //! �R���X�g���N�^
	~BoxObject();                  //! �f�X�g���N�^
	void Update();		
	Box * GetBoxCol(); //! ��`�̓�����̃Q�b�^�[

private:
	Box * mcpBoxCol;
};

