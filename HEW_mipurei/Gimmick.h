#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "Dynamo.h"
/* ---------------------------------------------------------------------------------- 
// �M�~�b�N�N���X�@                                                                //
// ��������N���X�ɂ��ăM�~�b�N�𐧍삵�Ă�������                                //
// �����蔻��͔h����̊�{��`�ł� ���̌`��̏ꍇ�͔h����ł��炽�ɍ���ĉ������� */

class Gimmick 
	: public AnimationHitObject
{
public:
	Gimmick();
	~Gimmick();

	void Update() override;
	virtual Box * GetBoxCol();
	void SetDynamo(Dynamo * _dynamo);
protected:

	Dynamo * mcpDynamo; //! ���̃M�~�b�N�̍쓮�̏����ɂȂ锭�d�@�̃|�C���^
	Box * mcpBoxCol;
	bool mActuation; //! �M�~�b�N�̍쓮�J�n�t���O
	bool mDoing; //! �M�~�b�N�쓮���t���O
	bool Sound = true;
};


