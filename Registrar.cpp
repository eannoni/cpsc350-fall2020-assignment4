#include "Registrar.h"

#include <bits/stdc++.h> // sort function

Registrar::Registrar() {
    clockTick = -1;
    studentIndex = 0;

    windowsSize = 5;
    studentsSize = 5;

    // stats
    meanStudentWaitTime = 0;
    medianStudentWaitTime = 0;
    longestStudentWaitTime = 0;
    numStudentsWaitOver10Min = 0;

    meanWindowIdleTime = 0;
    longestWindowIdleTime = 0;
    numWindowsIdleOver5Min = 0;

    windows = new Window*[windowsSize];
    students = new Student*[studentsSize];
    studentQueue = new GenQueue<Student>();
}

Registrar::Registrar(vector<int> *info) {
    clockTick = -1;
    studentIndex = 0;

    // stats
    meanStudentWaitTime = 0;
    medianStudentWaitTime = 0;
    longestStudentWaitTime = 0;
    numStudentsWaitOver10Min = 0;

    meanWindowIdleTime = 0;
    longestWindowIdleTime = 0;
    numWindowsIdleOver5Min = 0;

    setUp(info);
}

Registrar::~Registrar() {
    for(int i = 0; i < windowsSize; ++i)
        delete windows[i];

    delete[] windows;

    for(int i = 0; i < studentsSize; ++i)
        delete students[i];

    delete students;

    delete studentQueue;
}

// run simulation
void Registrar::simulate() {
    // loop while there are still students left to arrive, the queue isn't empty, or all windows aren't empty
    while((studentIndex < studentsSize) || !studentQueue->isEmpty() || !allWindowsAreEmpty()) {

        // increment tick
        clockTick++;

        // add Students from array to queue
        while(studentIndex < studentsSize) {
            if(students[studentIndex]->getArrivalTime() == clockTick)
                studentQueue->enqueue(students[studentIndex++]);
            else
                break;
        }

        // check windows, if occupied then either remove finished students or spend student time
        for(int i = 0; i < windowsSize; ++i) {
            Window *currWindow = windows[i];
            if(currWindow->isOccupied()) {
                currWindow->decrementCurrStudentWindowTime();
                if(currWindow->getCurrStudentWindowTime() == 0) {
                    currWindow->clearCurrStudent();
                    currWindow->wasOccupied = true;
                }
            }
        }

        // remove students from queue and add to window (if windows are open)
        while(!studentQueue->isEmpty()) { // while there is someone in line...
            int windowIndex = getNextOpenWindowIndex();
            if(windowIndex != -1) { // if there is a window open...
                // dequeue student and send to window
                Student *temp = studentQueue->dequeue();
                // set student's exit time
                temp->setExitTime(clockTick);
                windows[windowIndex]->setCurrStudent(temp);
            } else // if all windows are occupied
                break;
        }

        // spend window time only if the window has not been occupied this tick
        for(int i = 0; i < windowsSize; ++i) {
            Window *currWindow = windows[i];
            if(currWindow->wasOccupied)
                currWindow->wasOccupied = false;
            else if(!currWindow->isOccupied())
                currWindow->incrementIdleTime();
        }
    }
}

// calculate all statistics
void Registrar::calcStats() {
    //STUDENT STATS
    int *waitTimes = new int[studentsSize];
    // mean student wait time
    int totalStudentWaitTime = 0;
    int numStudentsWaiting = 0;
    for(int i = 0; i < studentsSize; ++i) {
        waitTimes[i] = students[i]->getTotalWaitTime(); // used in median calculation
        if(waitTimes[i] > 0) { // only calculate avgs of students that waited
            numStudentsWaiting++;
            totalStudentWaitTime += waitTimes[i];
        }
    }
    if(numStudentsWaiting == 0)
        numStudentsWaiting = 1;
    meanStudentWaitTime = (float)(totalStudentWaitTime) / (float)(numStudentsWaiting);
    // median student wait time
    sort(waitTimes, waitTimes + studentsSize);
    medianStudentWaitTime = waitTimes[studentsSize/2];
    // longest student wait time
    longestStudentWaitTime = waitTimes[studentsSize - 1];
    // number of students who waited over 10 minutes
    int sum = 0;
    for(int i = 0; i < studentsSize; ++i) {
        if(waitTimes[i] > 10) {
            sum += (studentsSize - i);
            break;
        }
    }
    numStudentsWaitOver10Min = sum;

    // WINDOW STATS
    int *idleTimes = new int[windowsSize];
    // mean window idle time
    int totalWindowIdleTime = 0;
    for(int i = 0; i < windowsSize; ++i) {
        idleTimes[i] = windows[i]->getIdleTime();
        totalWindowIdleTime += idleTimes[i];
    }
    meanWindowIdleTime = (float)totalWindowIdleTime / (float)windowsSize;
    // longest window idle time
    longestWindowIdleTime = idleTimes[windowsSize - 1];
    // number of windows with idle time over 5 minutes
    sum = 0;
    for(int i = 0; i < windowsSize; ++i) {
        if(idleTimes[i] > 5) {
            sum += (windowsSize - i);
            break;
        }
    }
    numWindowsIdleOver5Min = sum;
}

// prints all stats
void Registrar::printStats() {
    cout << "\n--------------| Simulation Stats |--------------\n" << endl;
    cout << "Students" << endl;
    cout << "\tMean wait time: \t\t" << meanStudentWaitTime << endl;
    cout << "\tMedian wait time: \t\t" << medianStudentWaitTime << endl;
    cout << "\tLongest wait time:\t\t" << longestStudentWaitTime << endl;
    cout << "\tAmount waited over 10 minutes:\t" << numStudentsWaitOver10Min << endl;

    cout << "Windows" << endl;
    cout << "\tMean idle time:\t\t\t" << meanWindowIdleTime << endl;
    cout << "\tLongest idle time:\t\t" << longestWindowIdleTime << endl;
    cout << "\tAmount idle over 5 minutes:\t" << numWindowsIdleOver5Min << endl;
    cout << "\n------------------------------------------------\n" << endl;
}

// for debugging
void Registrar::print() {
    cout << "------ REGISTRAR DATA: ------" << endl;
    cout << "\nClock Tick: " << clockTick << endl;
    cout << "\nWindows: " << windowsSize << endl;
    for(int i = 0; i < windowsSize; ++i) {
        cout << "\t" << windows[i]->toString() << endl;
    }
    cout << "\nStudents: " << studentsSize << endl;
    for(int i = 0; i < studentsSize; ++i) {
        cout << "\t" << students[i]->toString() << endl;
    }
    cout << "\nQueue size: " << studentQueue->getSize() << endl;
    cout << "\n-----------------------------\n" << endl;
}

// called from overloaded constructor to initialize variables
void Registrar::setUp(vector<int> *info) {
    // set sizes
    windowsSize = info->at(0);
    studentsSize = determineTotalStudents(info);
    // initialize and fill windows
    windows = new Window*[windowsSize];
    for(int i = 0; i < windowsSize; ++i) {
        windows[i] = new Window();
    }
    students = new Student*[studentsSize];
    // create Student objects and add to students array
    int currStudentIndex = -1; // index at which to add Student into students list
    int i = 1;
    while(i < info->size()) {
        int arrivalTime = info->at(i++);
        int amountOfStudents = info->at(i++);
        for(int j = 0; j < amountOfStudents; ++j) {
            int windowTime = info->at(i++);
            students[++currStudentIndex] = new Student(arrivalTime, windowTime);
        }
    }
    // initialize studentQueue
    studentQueue = new GenQueue<Student>();
}

// finds out how many students total
int Registrar::determineTotalStudents(vector<int> *info) {
    int i = 2;
    int totalStudents = 0;
    while(i < info->size()) {
        totalStudents += info->at(i);
        i += info->at(i) + 2;
    }
    return totalStudents;
}

// returns index of next open window (-1 if none found)
int Registrar::getNextOpenWindowIndex() {
    for(int i = 0; i < windowsSize; ++i) {
        if(!windows[i]->isOccupied())
            return i;
    }
    return -1;
}

// returns true if all windows are unoccupied
bool Registrar::allWindowsAreEmpty() {
    for(int i = 0; i < windowsSize; ++i) {
        if(windows[i]->isOccupied())
            return false;
    }
    return true;
}
