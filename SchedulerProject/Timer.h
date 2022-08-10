#pragma once
class Timer {
	static int time;
public:
	static int GetTime() {return Timer::time;}
	static void IncreaseTime() {Timer::time++;}
};
