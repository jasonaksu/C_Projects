#include "logger.h"

// Initializing the global logger instance with 0 steps counted.
log_t logger = {0};

// Function to reset the number of logged steps to 0
void logger_reset() {
  logger.num_steps = 0;
}

// Function to add a specified cost to the total count of logged steps.
void logger_add(int cost) {
  logger.num_steps += cost;
}
