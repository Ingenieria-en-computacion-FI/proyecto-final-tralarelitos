#ifndef LOGGER_H
#define LOGGER_H

void log_info(
     const char* msg
);

void log_event(
     const char* tag,
     int pid,
     int tick
);

#endif
