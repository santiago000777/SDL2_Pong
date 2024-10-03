#include "Timer.h"

unsigned long int Timer::GetDuration_ms() {
    return duration;
}

void Timer::SetFirst() {
    first = std::chrono::high_resolution_clock::now();
}

void Timer::SetSecond() {
    second = std::chrono::high_resolution_clock::now();
    
}

void Timer::CalculateDuration() {
    duration = (unsigned long int)std::chrono::duration_cast<std::chrono::milliseconds>(second - first).count();
}
