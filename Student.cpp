#include "Student.h"

Student::Student() {
    arrivalTime = 0;
    exitTime = -1;
    windowTime = 0;
}

Student::Student(int arrivalTime, int windowTime) {
    this->arrivalTime = arrivalTime;
    exitTime = -1;
    this->windowTime = windowTime;
}

Student::~Student() {}

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

void Student::setExitTime(int exitTime) {
    this->exitTime = exitTime;
}

void Student::spendWindowTime() {
    windowTime--;
}

string Student::toString() {
    return ("[STUDENT] Arrived at: " + to_string(arrivalTime) + ", exited at: " +
    to_string(exitTime) + ", time to spend at window: " + to_string(windowTime));
}
