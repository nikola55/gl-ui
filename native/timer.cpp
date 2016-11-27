#include "timer.h"


#define STONS(x)((x)*1000000000)
#define NS (1000000000)

using native::Timer;

Timer::Timer() {
#if defined(__linux) || defined(__unix)
    clock_gettime(CLOCK_MONOTONIC, &m_start);
#endif
}

void Timer::suspend(uint64_t nsec) {
#if defined(__linux) || defined(__unix)
    timespec ts = m_start;
    ts.tv_nsec += nsec;
    ts.tv_sec += ts.tv_nsec / NS;
    ts.tv_nsec %= NS;
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, 0);
#endif
}
