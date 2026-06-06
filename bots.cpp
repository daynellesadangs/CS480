/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #1, Thread Manager

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: bots.cpp
***********************************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "bots.h"

sem_t FLAG;

void* botRunner(void* arg){

    int threadNum = *static_cast<int*>(arg);

    for (int i = 0; i < NUM_RUNS; i++){
        if (threadNum % 2 == 0){
            sleep(2);
        }
        else{
            sleep(3);
        }

        sem_wait(&FLAG);

        std::ofstream quoteFile("QUOTE.txt", std::ios::app);
        if (!quoteFile){
            std::cerr << "Error opening QUOTE.txt\n";
            sem_post(&FLAG);
            pthread_exit(nullptr);
        }

        if (threadNum % 2 == 0){
            quoteFile << "Thread ID " << threadNum
                      << ": \"Controlling complexity is the essence of computer programming.\"\r\n"
                      << " --Brian Kernighan\r\n";
        } else {
            quoteFile << "Thread ID " << threadNum
                      << ": \"Computer science is no more about computers than astronomy is about telescopes.\"\r\n"
                      << " --Edsger Dijkstra\r\n";
        }

        std::cout << "Thread " << threadNum << " is running\n";

        quoteFile.close();
        sem_post(&FLAG);
    }
    pthread_exit(nullptr);
}

int main(){

    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    std::ofstream quoteFile("QUOTE.txt");
    if (!quoteFile){
        std::cerr << "Error creating QUOTE.txt\n";
        return 1;
    }

    quoteFile << "Process ID: " << getpid() << "\r\n";
    quoteFile.close();

    if (sem_init(&FLAG, 0, 1) != 0){
        std::cerr << "Error initializing semaphore\n";
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++){
        threadNums[i] = i + 1;

        std::cout << "Creating thread, in main(): " << threadNums[i] << "\n";

        if (pthread_create(&threads[i], nullptr, botRunner, &threadNums[i]) != 0){
            std::cerr << "Error creating thread " << threadNums[i] << "\n";
            sem_destroy(&FLAG);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], nullptr);
    }

    sem_destroy(&FLAG);
    std::cout << "All bot threads have finished. Program exiting gracefully.\n";

    return 0;
}