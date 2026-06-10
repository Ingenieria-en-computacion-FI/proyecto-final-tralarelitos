#ifndef PARSER_H
#define PARSER_H

#include "process.h"

int parser_load_processes(
     const char* filepath,
     Process* out,
     int max
);

#endif
