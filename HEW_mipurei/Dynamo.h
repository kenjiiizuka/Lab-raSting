#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "PlayerState.h"
class Dynamo :
	public AnimationHitObject
{
public:
	Dynamo();
	~Dynamo();

	//! �h����A���d���ꂽ��A�d�C���B�������Ƃ�ΏۂɃM�~�b�N�ɓ`����
	void Update();
	void Draw();
	virtual TailReaction ReturnReaction(float _power, bool _elect); //! �h����Ă����ۂɃ��A�N�V������Ԃ�
	virtual void SetChrage(bool _state);               //! ���d�@�̃`���[�W���ꂽ���ǂ����̃Z�b�^�[
	Box * GetBoxCol(); //! �����蔻��̃Q�b�^�[
	bool GetChargeState();  //! �`���[�W���ꂽ���ǂ�����Ԃ� 

protected:
	bool mCharge;      //! ���d���ꂽ���ǂ���
	bool Doing;        //! �`���[�W��
	bool mChargeFin;   //! �`���[�W����
	Box * mcpBox;      //! �����蔻��
private:
	
	Vector2 ColSize;   //! �����蔻��̃T�C�Y	
};
