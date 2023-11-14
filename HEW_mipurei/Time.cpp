#include "Time.h"

using namespace std::chrono;


double GetNowSeconds()
{
	return (double)(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count()) / 1000.0f;
}

double GetNowMinutes()
{
	return  (double)(duration_cast<seconds>(steady_clock::now().time_since_epoch()).count()) / 60.0f;
}

double GetNowMilliSeconds()
{
	return (double)(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

long long GetNowMicro()
{
	return std::chrono::duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
}


bool DelaySeconds(double _waitSeconds, double _startSeconds)
{
	if (GetNowSeconds() - _startSeconds >= _waitSeconds) {
		return true;
	}
	return false;
}


bool DelayMinutes(double _waitMinutes, double _startMinutes)
{
	if (GetNowMinutes() - _startMinutes >= _waitMinutes) {
		return true;
	}

	return false;
}
