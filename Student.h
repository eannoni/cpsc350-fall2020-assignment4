#ifndef STUDENT
#define STUDENT

#include <iostream>

using namespace std;

class Student {
    public:
        Student();
        Student(int arrivalTime, int windowTime);
        ~Student();

        int getArrivalTime();
        int getExitTime();
        int getWindowTime();
        int getTotalWaitTime();

        void setExitTime(int exitTime);
        void spendWindowTime(); // decrements windowTime

        string toString();

    private:
        int arrivalTime; // time arrived in queue
        int exitTime; // time left queue
        int windowTime; // how long to spend at window
};

#endif
