#include "Window.h"

Window::Window() {
    idleTime = 0;
    wasOccupied = false;
    currStudent = NULL;
}

Window::~Window() {
    currStudent = NULL;
}

int Window::getIdleTime() {
    return idleTime;
}

bool Window::isOccupied() {
    return (currStudent != NULL);
}

void Window::incrementIdleTime() {
    idleTime++;
}

int Window::getCurrStudentWindowTime() {
    return currStudent->getWindowTime();
}

void Window::decrementCurrStudentWindowTime() {
    currStudent->spendWindowTime();
}

void Window::setCurrStudent(Student *s) {
    currStudent = s;
}

void Window::clearCurrStudent() {
    currStudent = NULL;
}

string Window::toString() {
    return ("[Window] Idle time: " + to_string(idleTime) + ", occupied: " + to_string(isOccupied()));
}
