#pragma once
#include "GameObject.h"



/* =====================================================================
// StaticObject�N���X                                                 //
// �����Ȃ��I�u�W�F�N�g��`�悷��@�\�������Ă��܂�                   //
// ����� : �ђ� ���i                                                 */
class StaticObject :
	public GameObject
{
public:
	StaticObject();  //! �R���X�g���N�^
	~StaticObject(); //! �f�X�g���N�^
	void SetPos(float _x, float _y); //! ���W�̃Z�b�^�[
	void SetX(float _x);
	void SetY(float _y);
};

