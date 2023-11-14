#pragma once
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <thread>

class FPSControl
{
private:
	static uint64_t mTargetFPS;	                                                    // �ڕW��FPS
	static uint64_t mDefaultFPS;
	static double   mDeltaTime;                                                       // �t���[���Ԃ̌o�ߎ���
	static double   mLastTime;   // �O��t���[������

public:
	static void Init(uint64_t _targetFPS) {
		mDefaultFPS = _targetFPS;
		mTargetFPS = static_cast<uint64_t>(1000 * 1000) / _targetFPS;
		mLastTime = timeGetTime();
	}

	static void StartFrame() {
		double currentTime = timeGetTime(); // ���ݎ����̎擾	
		// �O��t���[������̌o�ߎ��Ԃ��擾
		double delta = currentTime - mLastTime;
		mDeltaTime = delta;

		if (mDeltaTime < mTargetFPS) {
			double sleep = (double)(mTargetFPS - mDeltaTime) / 1000.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep)));

			// �ҋ@��̎����X�V
			currentTime = timeGetTime(); // ���ݎ����̎擾
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

