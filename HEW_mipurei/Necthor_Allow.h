#pragma once
#include "AnimationHitObject.h"
class Necthor_Allow :
	public AnimationHitObject
{
public:
	Necthor_Allow();
	~Necthor_Allow();

	void Update();

	void AllowOn(Vector2 _pos);
	void AllowOff();
private:
	float AddY;     //! Y���W���ӂ�ӂ퓮�������߂̈ړ��ʂ����ϐ�
	float TotalYAdd; //! Y�̃g�[�^���̈ړ���
	float Arufa;    //! �����x
	float AddArufa; //! �����x�ɉ��Z�����
	bool AllowActiv = false; //! �I���I�t�ϐ�

};

