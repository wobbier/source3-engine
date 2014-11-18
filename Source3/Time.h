// Source3 Engine - 2014 Mitchell Andrews
#pragma once
#include <Windows.h>

/*
Clock.h
A simple high precision engine clock that utilizes system cpu ticks to determine
how much time has time has passed since the last computation.
2014 Mitch Andrews - Game Engine Design
*/
class Time {
	Time();
	~Time();
	static Time* mClock;
	LARGE_INTEGER mTicks;
	LARGE_INTEGER mTicksPerSecond;
	bool mHighResolutionSupport;

public:
	float deltaTime;
	//************************************
	// Method:    Get
	// FullName:  Clock::Get
	// Access:    public static
	// Returns:   Clock*
	// Qualifier: Get the clock instance for the engine.
	//************************************
	static Time* Get();

	//************************************
	// Method:    GetTimeInMilliseconds
	// FullName:  Clock::GetTimeInMilliseconds
	// Access:    public
	// Returns:   double
	// Qualifier: Converts clock ticks into milliseconds and returns it.
	//************************************
	float GetTimeInMilliseconds();

	//************************************
	// Method:    GetTimeInSeconds
	// FullName:  Clock::GetTimeInSeconds
	// Access:    public
	// Returns:   double
	// Qualifier: Converts clock ticks into seconds.
	//************************************
	float GetTimeInSeconds();

	//************************************
	// Method:    GetHardwareCounterValue
	// FullName:  Clock::GetHardwareCounterValue
	// Access:    public
	// Returns:   LARGE_INTEGER
	// Qualifier: Get the tick value from the cpu.
	//************************************
	LARGE_INTEGER GetHardwareCounterValue();

	//************************************
	// Method:    GetResolution
	// FullName:  Clock::GetResolution
	// Access:    public
	// Returns:   LARGE_INTEGER
	// Qualifier: Get ticks per second.
	//************************************
	LARGE_INTEGER GetResolution();

	//************************************
	// Method:    GetCurrentTicks
	// FullName:  Clock::GetCurrentTicks
	// Access:    public
	// Returns:   LARGE_INTEGER
	// Qualifier: Get total amount of ticks.
	//************************************
	LARGE_INTEGER GetCurrentTicks();

	//************************************
	// Method:    TicksToSeconds
	// FullName:  Clock::TicksToSeconds
	// Access:    public
	// Returns:   double
	// Qualifier: the amount of ticks converted to seconds.
	// Parameter: LARGE_INTEGER _ticks
	//************************************
	float TicksToSeconds(LARGE_INTEGER _ticks);

	//************************************
	// Method:    Ready
	// FullName:  Clock::Ready
	// Access:    public
	// Returns:   bool
	// Qualifier: Check if the cpu is ready to begin.
	//************************************
	bool Ready();

	//************************************
	// Method:    Ready
	// FullName:  Clock::Ready
	// Access:    public
	// Returns:   bool
	// Qualifier: Get the current total time in seconds.
	//************************************
	float GetCurrentTime();
};