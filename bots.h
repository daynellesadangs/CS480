/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #1, Thread Manager

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: bots.h
***********************************************************************/

#ifndef BOTS_H
#define BOTS_H

#include <semaphore.h>

constexpr int NUM_THREADS = 7;
constexpr int NUM_RUNS = 8;

extern sem_t FLAG;

void* botRunner(void* arg);

#endif
