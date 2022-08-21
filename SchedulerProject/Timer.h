#pragma once
#include <atomic>
class Timer {
	static std::atomic_int time;
public:
	static int GetTime() { return Timer::time; }
	static void IncreaseTime() { Timer::time++; }
};