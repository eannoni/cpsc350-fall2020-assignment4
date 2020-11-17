#include "Student.h"

// default constructor
Student::Student() {
    arrivalTime = 0;
    exitTime = -1;
    windowTime = 0;
}

// overloaded constructor
Student::Student(int arrivalTime, int windowTime) {
    this->arrivalTime = arrivalTime;
    exitTime = -1;
    this->windowTime = windowTime;
}

// destructor
Student::~Student() {}

// ACCESSORS

int Student::getArrivalTime() {
    return arrivalTime;
}

int Student::getExitTime() {
    return exitTime;
}

int Student::getWindowTime() {
    return windowTime;
}

int Student::getTotalWaitTime() {
    return (exitTime - arrivalTime);
}

// MUTATORS

void Student::setExitTime(int exitTime) {
    this->exitTime = exitTime;
}

// decremetns window time
void Student::spendWindowTime() {
    windowTime--;
}

// for debugging
string Student::toString() {
    return ("[STUDENT] Arrived at: " + to_string(arrivalTime) + ", exited at: " +
    to_string(exitTime) + ", time to spend at window: " + to_string(windowTime));
}
