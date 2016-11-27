#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#if defined(__linux) || defined(__unix)
#include <time.h>
#endif

namespace native {
class Timer {
#if defined(__linux) || defined(__unix)
    timespec m_start;
#endif
public:
    Timer();
    void suspend(uint64_t nsec);
};
}
#endif // TIMER_H
