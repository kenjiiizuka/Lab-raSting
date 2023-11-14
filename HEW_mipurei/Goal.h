#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "PlayerState.h"
#include "Image.h"
#include "AnimationHitObject.h"
/* ------------- 
// ���[��ł� */

class Goal :
	public AnimationHitObject
{
public:
	Goal();
	~Goal();

	void Update();
	void Draw();

	Box * GetBoxCol();
	bool GetGoal();    //! �S�[�������������炤
	TailReaction ReturnReaction(float _power);
	bool GetHit();                //! �q�b�g�������̃Q�b�^�[ �S�[���ɐK�����������特���Ƃ߂邽�߂�
	void SetGoaled(bool _goaled); //! �S�[���������Ƃɂ���
private:
	Box * mcpBox;
	bool Start;                          //! ���o���n�܂�t���O
	AnimationHitObject * PeaperStream;
	int YSplit;
	bool Hit;
	bool Hited;
	bool mGoal;
	int FrameCnt; //! �S�[���̉��o�̂��߂̃t���[���𐔂���
};

