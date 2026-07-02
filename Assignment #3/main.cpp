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


// returns a random list of disk cylinder requests
vector<int> generateRequests(int length) {
    vector<int> requests;

    for (int i = 0; i < length; i++) {
        requests.push_back(rand() % 1000);
    }
    return requests;
}

// FCFS Algorithm
// goes through the requests in the order they appear
int fcfs(const vector<int>& requests, int start) {
    int totalDistance = 0;
    int current = start;

    for (int request : requests) {
        totalDistance += abs(request - current);
        current = request;
    }

    return totalDistance;
}

// SSTF Algorithm
// chooses the request closest to the current position
int sstf(vector<int> requests, int start) {
    int totalDistance = 0;
    int current = start;

    // keeps running until every request is handled
    while (!requests.empty()) {
        int closestIndex = 0;
        int closestDistance = abs(requests[0] - current);

        // looks for closest request
        for (int i = 1; i < (int)requests.size(); i++) {
            int distance = abs(requests[i] - current);

            if (distance < closestDistance) {
                closestDistance = distance;
                closestIndex = i;
            }
        }

        // moves to the closest request
        totalDistance += closestDistance;
        current = requests[closestIndex];

        // removes the completed request from list
        requests.erase(requests.begin() + closestIndex);
    }

    return totalDistance;
}

// SCAN Algorithm
// moves right, then turns around and moves left
int scan(vector<int> requests, int start) {
    int totalDistance = 0;
    int current = start;

    // sorts the requests in order
    sort(requests.begin(), requests.end());

    vector<int> left;
    vector<int> right;

    // splits requests based on the starting position
    for (int request : requests) {
        if (request < start) {
            left.push_back(request);
        } else {
            right.push_back(request);
        }
    }

    // handles all reqeusts to the right first
    for (int request : right) {
        totalDistance += abs(request - current);
        current = request;
    }

    // if there are requests on the left, it goes to the end first
    if (!left.empty()) {
        totalDistance += abs(MAX_CYLINDER - current);
        current = MAX_CYLINDER;

        // then moves left and handles those requests
        for (int i = (int)left.size() - 1; i >= 0; i--) {
            totalDistance += abs(left[i] - current);
            current = left[i];
        }
    }

    return totalDistance;
}

int main(int argc, char* argv[]) {

    // checks length of user's sequence
    if (argc != 2) {
        cerr << "Usage: simarm <sequence_length>" << endl;
        return 1;
    }

    int length = atoi(argv[1]);

    // makes sure input is valid
    if (length <= 0) {
        cerr << "Error: sequence length must be positive." << endl;
        return 1;
    }

    // starts random number generator
    srand(time(NULL));

    int startCylinder = 500;

    // creates random request list
    vector<int> requests = generateRequests(length);

    // prints request list
    cout << "Generated sequence:" << endl;
    for (int request : requests) {
        cout << request << " ";
    }
    cout << endl << endl;

    // prints the results of each algorithm
    cout << "Starting cylinder: " << startCylinder << endl;
    cout << "FCFS total distance: " << fcfs(requests, startCylinder) << endl;
    cout << "SSTF total distance: " << sstf(requests, startCylinder) << endl;
    cout << "SCAN total distance: " << scan(requests, startCylinder) << endl;

    return 0;
}

/************************[ EOF: main.cpp ]***************************/
