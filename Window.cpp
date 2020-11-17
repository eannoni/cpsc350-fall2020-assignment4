#include "Window.h"

// default constructor
Window::Window() {
    idleTime = 0;
    wasOccupied = false;
    currStudent = NULL;
}

// destructor
Window::~Window() {
    currStudent = NULL;
}

// returns idle time
int Window::getIdleTime() {
    return idleTime;
}

// returns true if window has a current student
bool Window::isOccupied() {
    return (currStudent != NULL);
}

// increments idle time
void Window::incrementIdleTime() {
    idleTime++;
}

// returns window time left for this student
int Window::getCurrStudentWindowTime() {
    return currStudent->getWindowTime();
}

// decrements this student's window time
void Window::decrementCurrStudentWindowTime() {
    currStudent->spendWindowTime();
}

// assigns current student pointer
void Window::setCurrStudent(Student *s) {
    currStudent = s;
}

// clears current student pointer
void Window::clearCurrStudent() {
    currStudent = NULL;
}

// for debugging
string Window::toString() {
    return ("[Window] Idle time: " + to_string(idleTime) + ", occupied: " + to_string(isOccupied()));
}
