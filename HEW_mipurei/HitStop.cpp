#include "HitStop.h"
#include "FrameRateCalculator.h"
#include "AnimationHitObject.h"


HitStop::HitStop(Character * _mcpHitAnimSprite)
{
	mcpHitStopAnimation = _mcpHitAnimSprite;
	HitStopFlg = false;	//! �q�b�g�X�g�b�v���s�������f�@�������͋U����X�^�[�g 
	HitJudge = false;	//! ���W���Ƃ邩���f�@�������͋U����X�^�[�g
	HitCount = 0;		//! �J�E���g�̏�����
}

HitStop::~HitStop()
{

}

int HitStop::HitStopStart(int _HitMax)
{

	HitStopFlg = true;	//! �q�b�g�X�g�b�v�t���O�@�I��

	HitMax = _HitMax;	//! ������ϐ��ɑ��

	return HitMax;		//! �����Ԃ�
}


bool HitStop::HitStoptime()
{
	if (HitJudge == false)
	{
		//! ���W���Ƃ�
		stoppos = mcpHitStopAnimation->GetVec();
	}

	//! �q�b�g�X�g�b�v�n�܂�
	if (HitStopFlg)		//! �t���O�����̏ꍇ
	{
		//! �����œn���ꂽ�l�ɂȂ�܂ŃJ�E���g
		if (HitCount <= HitMax)
		{
			HitCount++;		//! �J�E���g�{
			HitJudge = true;	//! ���W���Ƃ�̂���߂�
			mcpHitStopAnimation->SetVec(stoppos);	//! �Ƃ������W�łƂǂ܂葱����
			mcpHitStopAnimation->GetAnimSprite()->SetAnimSpeed(300);	//! �A�j���[�V�����X�s�[�h�������ĂƂ܂��Ă���悤�Ɍ�����
		}
		if (HitCount >= HitMax)		//! �����������
		{
			HitStopFlg = false;		//! �q�b�g�X�g�b�v�t���O�̃��Z�b�g
			HitJudge = false;		//! ���W�t���O�̃��Z�b�g
			HitCount = 0;			//! �J�E���g�̃��Z�b�g
			HitMax = 0;				//! ����̃��Z�b�g
			mcpHitStopAnimation->GetAnimSprite()->SetAnimSpeed(8);		//! �A�j���[�V�����X�s�[�h�����ɖ߂�
		}
	}
	return HitStopFlg;		//! �q�b�g�X�g�b�v�t���O��Ԃ��@�����false
}

//! ���W����邩�ǂ����̃Q�b�^�[
bool HitStop::GetHitJugde()
{
	return HitJudge;		//! ���W�t���O��Ԃ�
}

