// Source3 Engine - 2014 Mitchell Andrews
#include "Time.h"

Time* Time::mClock = 0;

Time::Time() {
	mTicks = GetHardwareCounterValue();
	mHighResolutionSupport = false;
	mHighResolutionSupport = (bool)QueryPerformanceFrequency(&mTicksPerSecond);
	mTicksPerSecond.QuadPart /= 1000.0f;
	deltaTime = 0.0001f;
}

Time::~Time() {
	delete mClock;
}

Time* Time::Get() {
	if (mClock) {
		return mClock;
	}
	else {
		return mClock = new Time();
	}
}

LARGE_INTEGER Time::GetHardwareCounterValue() {
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);
	return v;
}

float Time::GetTimeInMilliseconds() {
	return GetTimeInSeconds() / 1000.0f;
}

float Time::GetTimeInSeconds() {
	LARGE_INTEGER ticks = GetHardwareCounterValue();
	double time = (ticks.QuadPart - mTicks.QuadPart) / mTicksPerSecond.QuadPart;
	mTicks = ticks;
	return (float)time;
}

float Time::TicksToSeconds(LARGE_INTEGER _ticks) {
	return ((float)_ticks.QuadPart - mTicks.QuadPart) / ((float)mTicksPerSecond.QuadPart);
}

LARGE_INTEGER Time::GetResolution() {
	return mTicksPerSecond;
}

LARGE_INTEGER Time::GetCurrentTicks() {
	return GetHardwareCounterValue();
}

float Time::GetCurrentTime() {
	return TicksToSeconds(GetCurrentTicks());
}

bool Time::Ready() {
	return mHighResolutionSupport;
}