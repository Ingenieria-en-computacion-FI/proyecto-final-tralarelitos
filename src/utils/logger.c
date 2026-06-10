#include <stdio.h>
#include <time.h>
#include "logger.h"

void log_info(const char* msg) {
     printf("[INFO]  %s\n", msg);
}

void log_event(const char* tag, int pid, int tick) {
     printf("[%-8s] tick=%-4d pid=%d\n", tag, tick, pid);
}
