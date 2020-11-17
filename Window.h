#ifndef WINDOW
#define WINDOW

#include "Student.h"

#include <iostream>

using namespace std;

class Window {
    public:
        Window(); // default constructor
        ~Window(); // destructor

        int getIdleTime(); // returns idle time
        bool isOccupied(); // returns true if window has a current student

        void incrementIdleTime(); // increments idle time

        int getCurrStudentWindowTime(); // returns window time left for this student
        void decrementCurrStudentWindowTime(); // decrements this student's window time
        void setCurrStudent(Student *s); // assigns current student pointer
        void clearCurrStudent(); // clears current student pointer

        string toString(); // for debugging

        Student *currStudent; // pointer to current student at this window
        bool wasOccupied; // is set as true when a student leaves a window, and set back to false for next tick

    private:
        int idleTime; // amount of time a window has not had a student
};

#endif
