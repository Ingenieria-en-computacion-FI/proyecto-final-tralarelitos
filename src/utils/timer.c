#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include "timer.h"

static struct timespec _start;

void timer_start() {
     clock_gettime(CLOCK_MONOTONIC, &_start);
}

double timer_elapsed_ms() {
     struct timespec now;
     clock_gettime(CLOCK_MONOTONIC, &now);
     return (now.tv_sec  - _start.tv_sec)  * 1000.0 + (now.tv_nsec - _start.tv_nsec) / 1e6;
}
