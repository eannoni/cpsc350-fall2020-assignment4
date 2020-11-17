#ifndef WINDOW
#define WINDOW

#include "Student.h"

#include <iostream>

using namespace std;

class Window {
    public:
        Window();
        ~Window();
        int getIdleTime();
        bool isOccupied();

        void incrementIdleTime();

        int getCurrStudentWindowTime();
        void decrementCurrStudentWindowTime();
        void setCurrStudent(Student *s);
        void clearCurrStudent();

        string toString();

        Student *currStudent;
        bool wasOccupied;

    private:
        int idleTime;
};

#endif
