#pragma once
#include "AnimationHitObject.h"
#include "PlayerState.h"
#include "Box.h"

//! ����I�u�W�F�N�g�ł��@

class BreakObj :
	public AnimationHitObject
{
public:
	BreakObj();
	~BreakObj();
	void Update() override;
	void Draw() override;
	Box * GetBoxCol();
	TailReaction ReturnReaction(float _power);
	bool GetBreaked(); //! �󂳂ꂽ��
private:
	Box * mcpBox;   //! ��`�̓����蔻��
	bool mBreak;    //! ��ꂽ�ǂ����̃t���O
	bool mBreaked;  //! ���ď������t���O
	int Cnt;         //! ���Ă���t���[���𐔂���
	float Arufa;
};

