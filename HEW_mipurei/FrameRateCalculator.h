#pragma once

// �t���[�����[�g�v�Z�N���X
class FrameRateCalculator
{
public:
	FrameRateCalculator();
	~FrameRateCalculator();

	float Update();
private:
	long long mCnt;
	const int mLimit = 60;
	float fps;
	long long mTime;

	long long CurrentTime();  // ���ݎ��Ԃ��擾
	void UpdateStr();         // �t���[�����[�g�̌v�Z�ƌ��ʂ𕶎���ɂ���
};

