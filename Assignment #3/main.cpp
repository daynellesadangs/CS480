/**********************************************************************
* Course: CS 480-01, Summer 2026
* Instructor: Guy Leonard
* Assignment Information: Programming Assignment #3, Disk Arm Scheduling Algorithms

* Team Members:
* - Daynelle Lorin Sadangsal (cssc3154)
* - Sophia Phung (cssc3147)

* FileName: main.cpp
***********************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

const int MIN_CYLINDER = 0;
const int MAX_CYLINDER = 999;

/*
 * Generate a random sequence of disk cylinder requests.
 */
vector<int> generateRequests(int length) {
    vector<int> requests;

    for (int i = 0; i < length; i++) {
        requests.push_back(rand() % 1000);
    }

    return requests;
}

/*
 * First-Come, First-Served disk scheduling.
 */
int fcfs(const vector<int>& requests, int start) {
    int totalDistance = 0;
    int current = start;

    for (int request : requests) {
        totalDistance += abs(request - current);
        current = request;
    }

    return totalDistance;
}

/*
 * Shortest Seek Time First disk scheduling.
 */
int sstf(vector<int> requests, int start) {
    int totalDistance = 0;
    int current = start;

    while (!requests.empty()) {
        int closestIndex = 0;
        int closestDistance = abs(requests[0] - current);

        for (int i = 1; i < (int)requests.size(); i++) {
            int distance = abs(requests[i] - current);

            if (distance < closestDistance) {
                closestDistance = distance;
                closestIndex = i;
            }
        }

        totalDistance += closestDistance;
        current = requests[closestIndex];
        requests.erase(requests.begin() + closestIndex);
    }

    return totalDistance;
}

/*
 * SCAN disk scheduling.
 * This version moves upward first, then reverses direction.
 */
int scan(vector<int> requests, int start) {
    int totalDistance = 0;
    int current = start;

    sort(requests.begin(), requests.end());

    vector<int> left;
    vector<int> right;

    for (int request : requests) {
        if (request < start) {
            left.push_back(request);
        } else {
            right.push_back(request);
        }
    }

    for (int request : right) {
        totalDistance += abs(request - current);
        current = request;
    }

    if (!left.empty()) {
        totalDistance += abs(MAX_CYLINDER - current);
        current = MAX_CYLINDER;

        for (int i = (int)left.size() - 1; i >= 0; i--) {
            totalDistance += abs(left[i] - current);
            current = left[i];
        }
    }

    return totalDistance;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: simarm <sequence_length>" << endl;
        return 1;
    }

    int length = atoi(argv[1]);

    if (length <= 0) {
        cerr << "Error: sequence length must be positive." << endl;
        return 1;
    }

    srand(time(NULL));

    int startCylinder = 500;
    vector<int> requests = generateRequests(length);

    cout << "Generated sequence:" << endl;
    for (int request : requests) {
        cout << request << " ";
    }
    cout << endl << endl;

    cout << "Starting cylinder: " << startCylinder << endl;
    cout << "FCFS total distance: " << fcfs(requests, startCylinder) << endl;
    cout << "SSTF total distance: " << sstf(requests, startCylinder) << endl;
    cout << "SCAN total distance: " << scan(requests, startCylinder) << endl;

    return 0;
}

/************************[ EOF: main.cpp ]***************************/