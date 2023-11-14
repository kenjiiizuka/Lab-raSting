#pragma once
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <thread>

class FPSControl
{
private:
	static uint64_t mTargetFPS;	                                                    // 目標のFPS
	static uint64_t mDefaultFPS;
	static double   mDeltaTime;                                                       // フレーム間の経過時間
	static double   mLastTime;   // 前回フレーム時間

public:
	static void Init(uint64_t _targetFPS) {
		mDefaultFPS = _targetFPS;
		mTargetFPS = static_cast<uint64_t>(1000 * 1000) / _targetFPS;
		mLastTime = timeGetTime();
	}

	static void StartFrame() {
		double currentTime = timeGetTime(); // 現在時刻の取得	
		// 前回フレームからの経過時間を取得
		double delta = currentTime - mLastTime;
		mDeltaTime = delta;

		if (mDeltaTime < mTargetFPS) {
			double sleep = (double)(mTargetFPS - mDeltaTime) / 1000.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep)));

			// 待機後の時刻更新
			currentTime = timeGetTime(); // 現在時刻の取得
			delta = currentTime - mLastTime;
			mDeltaTime = delta;
		}
		mLastTime = currentTime;
	}

	static double GetDeltaTime() {
		return (double)mDeltaTime / 1000;
	}

	static uint64_t GetTargetFPS() {
		return mTargetFPS;
	}

	static uint64_t GetDefaultFPS() {
		return mDefaultFPS;
	}


};

