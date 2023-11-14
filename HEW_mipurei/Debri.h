#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

//! �l�N�g�[���̍U���ŏo�Ă��邪�ꂫ�ł�
//! �����l�̓l�N�g�[������ݒ肷��

class NecthorDebri :
	public AnimationHitObject
{
	enum eDebreState{
		State_Up,
		State_Fadeout, 
		State_None
	};

public:
	NecthorDebri();
	~NecthorDebri();

	void Update();
	void Draw();
	void UpStart(Vector2 _initpos, bool _drawstate = false);  //! ���ꂫ���o�Ă���
	void FadeoutStart(); //! ���ꂫ��������
	Box * GetCol();
private:
	void Up();        //! ���ꂫ���o�Ă��鏈��
	void Fadeout();   //! ���ꂫ�������鏈��


	Box * mcpBox;
	eDebreState State;
	
	float totalUp;
	float Arufa; //! �����x
};

