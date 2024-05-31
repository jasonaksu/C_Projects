#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "macros.h"

typedef struct log {
  int num_steps;
} log_t;


extern log_t logger;


void logger_reset();
void logger_add(int cost);

// Using LOG from macros.h to enable disable logging.
#ifdef LOG
#define LOG_OPERATION(cost) logger_add(cost)
#else
#define LOG_OPERATION(cost)
#endif

#endif
