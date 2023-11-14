#pragma once
#include "AnimationHitObject.h"

//! �e�N�X�`�����Ђ���Ă�����Ȃ̂ŁA��p�ɍ��܂�
class Smoke :
	public AnimationHitObject
{
	enum SmokeState {
		State_FadeIn,
		State_FadeOut,
		State_None,
	};
public:
	Smoke();
	~Smoke();

	void Update();
	void Draw();

	//! �����o���p�̊֐�
	void NomalSmokeSmall(Vector2 _pos);   //! �^��Ɍ������Ăł鉌
	void LeftSmokeSmall(Vector2 _pos);    //! ����Ɍ������Ăł鉌
	void RightSmokeSmall(Vector2 _pos);   //! �E��Ɍ������Ăł鉌
	void NomalSmokeRagular(Vector2 _pos); //! �^��Ɍ������Ăł鉌(��)
	void SmokeOff();        //! ���̃A�j���V��������߂�
	bool GetSmokeActiv();   //! �������o�Ă��邩���擾����
private:
	SmokeState State;
	bool SmokeActiv = false;
	float Arufa;
};

