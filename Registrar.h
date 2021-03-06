// Registrar header
#ifndef REGISTRAR
#define REGISTRAR

#include "GenQueue.h"
#include "Window.h"
#include "Student.h"

#include <iostream>
#include <vector>

using namespace std;

class Registrar {

    public:
        Registrar(); // default constructor
        Registrar(vector<int> *info); // overloaded constructor
        ~Registrar(); // destructor

        void simulate(); // run simulation
        void calcStats(); // calculate all statistics
        void printStats(); // print statistics calculated

        void print(); // for debugging

        // stats
        float meanStudentWaitTime;
        float medianStudentWaitTime;
        int longestStudentWaitTime;
        int numStudentsWaitOver10Min;

        float meanWindowIdleTime;
        int longestWindowIdleTime;
        int numWindowsIdleOver5Min;

    private:
        Window **windows; // array of all windows
        Student **students; // array of all students
        GenQueue<Student> *studentQueue; // queue of students from all students

        int clockTick; // global time that increases each round
        int studentIndex; // keeps track of position in the students array

        int windowsSize; // num of windows in array
        int studentsSize; // num of students in array

        void setUp(vector<int> *info); // called from overloaded constructor to initialize variables
        int determineTotalStudents(vector<int> *info); // finds out how many students total
        int getNextOpenWindowIndex(); // returns index of next open window (-1 if none found)
        bool allWindowsAreEmpty(); // returns true if all windows are unoccupied
};

#endif
