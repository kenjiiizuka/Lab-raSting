#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

/* --------------- 
// ���ԃ|�C���g */

class CheackPoint :
	public AnimationHitObject
{
public:
	CheackPoint();
	~CheackPoint();
	void Update() override;
	void HitCheckPoint(); //! ���ԂɐG�ꂽ
	bool GetCheck();      //! ���ԂɐG�ꂽ���ǂ����̃Q�b�^�[
	Box * GetBox();       //! ��`�̓�����Q�b�^�[
private:
	Box * mcpBox;   //! ��`�̓�����
	bool Check;     //! ���ԂɐG�ꂽ���ǂ���
	bool Sound = false; //! SE���Ȃ炵�����ǂ���
};

