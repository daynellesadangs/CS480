#ifndef BOTS_H
#define BOTS_H

#include <semaphore.h>

constexpr int NUM_THREADS = 7;
constexpr int NUM_RUNS = 8;

extern sem_t FLAG;

void* botRunner(void* arg);

#endif
