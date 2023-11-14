#pragma once
#include "AnimationHitObject.h"
#include <memory>
//! �v���C���[��p�̂΂��Ă�[UI

class PlayerBattery
{
public:
	PlayerBattery();
	~PlayerBattery();

	void Update(int _charge);
	void Draw();
private:
	int DifCharge; //! ���݂̃`���[�W�����ƕ\����ł̍�(�d�r�����Ԃɂ��܂銴���ɂ������̑����Ă���t���[���������Ď��𑝂₷�悤�ɂ�����)
	int NowCharge;
	//! �o�b�e���[�̌��݂̕\�����
	int NumBattryDraw;  //! ���݂̃`���[�W�̐��Ɠ����ɂȂ�悤�ɁA�`�悷��
	int WaitFrameCnt;   //! ���t���[���҂��Ă���`���؂�ւ��邽�߂̕ϐ�
	int WaitFrameLow;   //! ��C�Ɍ���̂��C���������̂ł������܂��Ă��猸�邽�߂̕ϐ�
	bool Up;            //! ������
	bool Down;          //! ������
	bool Wait;
	std::unique_ptr<AnimationHitObject> Battery;
};

