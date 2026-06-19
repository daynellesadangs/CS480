/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #1, Thread Manager

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: bots.cpp
* C++ file for main functions of program
***********************************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "bots.h"

sem_t FLAG; // Access manager to file QUOTE.txt, acts as lock

// Method for threads writing to QUOTE.txt
void* botRunner(void* arg){

    // Set current thread number
    int threadNum = *static_cast<int*>(arg);

    // Ensures even numbered-threads wait for 2 seconds, while odd-numbered waits for 3
    for (int i = 0; i < NUM_RUNS; i++){
        if (threadNum % 2 == 0){
            sleep(2);
        }
        else{
            sleep(3);
        }

        // Sets the semaphore FLAG to wait so only one thread can access QUOTE.txt at a time
        sem_wait(&FLAG);

        // Check if QUOTE.txt exists, otherwise exit process
        std::ofstream quoteFile("QUOTE.txt", std::ios::app);
        if (!quoteFile){
            std::cerr << "Error opening QUOTE.txt\n";
            sem_post(&FLAG);
            pthread_exit(nullptr);
        }

        // Write even-numbered thread quote to Kernighan in QUOTE.txt
        if (threadNum % 2 == 0){
            quoteFile << "Thread ID " << threadNum
                      << ": \"Controlling complexity is the essence of computer programming.\"\r\n"
                      << " --Brian Kernighan\r\n";
        // Otherwise, write odd-numbered thread quote to Dijkstra in QUOTE.txt
        } else {
            quoteFile << "Thread ID " << threadNum
                      << ": \"Computer science is no more about computers than astronomy is about telescopes.\"\r\n"
                      << " --Edsger Dijkstra\r\n";
        }

        // Print in terminal which thread number is running
        std::cout << "Thread " << threadNum << " is running\n";

        // QUOTE.txt is closed for editing and the semaphore FLAG is posted for another thread entry
        quoteFile.close();
        sem_post(&FLAG);
    }
    // Exit process after thread has run NUM_RUNS amount of times
    pthread_exit(nullptr);
}

int main(){

    // Set process threads and thread numbers to NUM_THREADS established in bots.h
    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    // Create QUOTE.txt file, if it cannot be created, return an error
    std::ofstream quoteFile("QUOTE.txt");
    if (!quoteFile){
        std::cerr << "Error creating QUOTE.txt\n";
        return 1;
    }

    // Print Process ID at top of QUOTE.txt file
    quoteFile << "Process ID: " << getpid() << "\r\n";
    quoteFile.close();

    /*
    * Initialize semaphore FLAG
    * PARAM:
    * &FLAG - address space of semaphore,
    * 0 - semaphore is shared between threads of current process,
    * 1 - initial semaphore value. Only allows one thread at a time to enter shared resource section.
    */
    if (sem_init(&FLAG, 0, 1) != 0){
        std::cerr << "Error initializing semaphore\n";
        return 1;
    }

    // Creates each thread to prepare for writing, if cannot, return error
    for (int i = 0; i < NUM_THREADS; i++){
        threadNums[i] = i + 1;

        std::cout << "Creating thread, in main(): " << threadNums[i] << "\n";

        if (pthread_create(&threads[i], nullptr, botRunner, &threadNums[i]) != 0){
            std::cerr << "Error creating thread " << threadNums[i] << "\n";
            sem_destroy(&FLAG);
            return 1;
        }
    }

    // Wait for all threads to finish before returning to main program
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], nullptr);
    }

    // When finished using semaphore, destroys it, and prints program exit in terminal
    sem_destroy(&FLAG);
    std::cout << "All bot threads have finished. Program exiting gracefully.\n";

    return 0;
}