#pragma once
#include <chrono>
#include <functional>

//using namespace std;

double GetNowSeconds();

double GetNowMinutes();

double GetNowMilliSeconds();

long long GetNowMicro();

bool DelaySeconds(double _waitTime, double _startTime);

bool DelayMinutes(double _waitTime, double _startTime);

