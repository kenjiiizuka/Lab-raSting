#pragma once

// フレームレート計算クラス
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

	long long CurrentTime();  // 現在時間を取得
	void UpdateStr();         // フレームレートの計算と結果を文字列にする
};

