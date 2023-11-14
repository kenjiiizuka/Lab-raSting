#include "FPSControll.h"

double   FPSControl::mDeltaTime = 0;
uint64_t FPSControl::mTargetFPS = 0;
double   FPSControl::mLastTime{};
uint64_t FPSControl::mDefaultFPS = 60;