#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "bots.h"

using namespace std;

// Global semaphore shared by all seven threads.
sem_t FLAG;

/*
 * botRunner
 *
 * Each thread sleeps based on whether its assigned number is even or odd.
 * Even-numbered threads sleep for 2 seconds.
 * Odd-numbered threads sleep for 3 seconds.
 *
 * The semaphore FLAG protects the shared file QUOTE.txt so that only one
 * thread writes to the file at a time.
 */
void* botRunner(void* arg)
{
    int threadNum = *static_cast<int*>(arg);

    for (int i = 0; i < NUM_RUNS; i++)
    {
        if (threadNum % 2 == 0)
        {
            sleep(2);
        }
        else
        {
            sleep(3);
        }

        sem_wait(&FLAG);

        ofstream quoteFile;
        quoteFile.open("QUOTE.txt", ios::app);

        if (!quoteFile)
        {
            cerr << "Error opening QUOTE.txt" << endl;
            sem_post(&FLAG);
            pthread_exit(nullptr);
        }

        if (threadNum % 2 == 0)
        {
            quoteFile << "Thread ID" << threadNum
                      << " \": Controlling complexity is the essence of computer programming.\"\r\n"
                      << " --Brian Kernighan\r\n";
        }
        else
        {
            quoteFile << "Thread ID" << threadNum
                      << " \": Computer science is no more about computers than astronomy is about telescopes.\"\r\n"
                      << " --Edsger Dijkstra\r\n";
        }

        cout << "Thread " << threadNum << " is running" << endl;

        quoteFile.close();

        sem_post(&FLAG);
    }

    pthread_exit(nullptr);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    ofstream quoteFile("QUOTE.txt");

    if (!quoteFile)
    {
        cerr << "Error creating QUOTE.txt" << endl;
        return 1;
    }

    quoteFile << getpid() << "\r\n";
    quoteFile.close();

    if (sem_init(&FLAG, 0, 1) != 0)
    {
        cerr << "Error initializing semaphore" << endl;
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadNums[i] = i;

        if (pthread_create(&threads[i], nullptr, botRunner, &threadNums[i]) != 0)
        {
            cerr << "Error creating thread " << i << endl;
            sem_destroy(&FLAG);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], nullptr);
    }

    sem_destroy(&FLAG);

    cout << "All bot threads have finished. Program exiting gracefully." << endl;

    return 0;
}