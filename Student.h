#ifndef STUDENT
#define STUDENT

#include <iostream>

using namespace std;

class Student {
    public:
        Student(); // default constructor
        Student(int arrivalTime, int windowTime); // overloaded constructor
        ~Student(); // destructor

        // accessors
        int getArrivalTime();
        int getExitTime();
        int getWindowTime();
        int getTotalWaitTime();

        // mutators
        void setExitTime(int exitTime);
        void spendWindowTime(); // decrements windowTime

        string toString(); // for debugging

    private:
        int arrivalTime; // time arrived in queue
        int exitTime; // time left queue
        int windowTime; // how long to spend at window
};

#endif
