#include "FrameRateCalculator.h"
#include <string>
#include <chrono>

FrameRateCalculator::FrameRateCalculator()
{
	mCnt = 0;
	fps = 0.0f;
	mTime = CurrentTime();
}

FrameRateCalculator::~FrameRateCalculator()
{
}

float FrameRateCalculator::Update()
{
	mCnt += 1;
	// �K��t���[���ɐ��ɂȂ�����t���[�����[�g�̂̍X�V
	if (mLimit <= mCnt) {
		UpdateStr();
	}
	return fps;
}

// �t���[���[�ƍX�V
//std::string * FrameRateCalculator::Update()
//{
//	mCnt += 1;
//	// �K��t���[���ɐ��ɂȂ�����t���[�����[�g�̂̍X�V
//	if (mLimit <= mCnt) {
//		UpdateStr();
//	}
//	return &FpsStr;
//}



// ���ݎ��Ԃ��擾����֐�
long long FrameRateCalculator::CurrentTime()
{
	std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

// �t���[�����[�g�̌v�Z�ƌ��ʂ𕶎���ɂ���
void FrameRateCalculator::UpdateStr()
{
	// fps���v�Z���A������Ƃ��ĕێ�����
	long long end = CurrentTime();
	double fpsResult = (double)(1000) / (end - mTime) * mCnt;
	mTime = end;
	fps = fpsResult;
	mCnt = 0;
}

/*// �t���[�����[�g�̌v�Z�ƌ��ʂ𕶎���ɂ���
void FrameRateCalculator::UpdateStr()
{
	// fps���v�Z���A������Ƃ��ĕێ�����
	long long end = CurrentTime();
	double fpsResult = (double)(1000) / (end - mTime) * mCnt;
	mTime = end;
	FpsStr = std::to_string(fpsResult) + "fps";
	mCnt = 0;
}
*/