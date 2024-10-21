#pragma once
#include "common.h"

class Timer {
public:
	Timer() {}
	void SetFirst();
	void SetSecond();
	void CalculateDuration();

	unsigned long int GetDuration_ms();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	unsigned long int duration {0};
};

