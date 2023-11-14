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
	// 規定フレームに数になったらフレームレートのの更新
	if (mLimit <= mCnt) {
		UpdateStr();
	}
	return fps;
}

// フレームーと更新
//std::string * FrameRateCalculator::Update()
//{
//	mCnt += 1;
//	// 規定フレームに数になったらフレームレートのの更新
//	if (mLimit <= mCnt) {
//		UpdateStr();
//	}
//	return &FpsStr;
//}



// 現在時間を取得する関数
long long FrameRateCalculator::CurrentTime()
{
	std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

// フレームレートの計算と結果を文字列にする
void FrameRateCalculator::UpdateStr()
{
	// fpsを計算し、文字列として保持する
	long long end = CurrentTime();
	double fpsResult = (double)(1000) / (end - mTime) * mCnt;
	mTime = end;
	fps = fpsResult;
	mCnt = 0;
}

/*// フレームレートの計算と結果を文字列にする
void FrameRateCalculator::UpdateStr()
{
	// fpsを計算し、文字列として保持する
	long long end = CurrentTime();
	double fpsResult = (double)(1000) / (end - mTime) * mCnt;
	mTime = end;
	FpsStr = std::to_string(fpsResult) + "fps";
	mCnt = 0;
}
*/