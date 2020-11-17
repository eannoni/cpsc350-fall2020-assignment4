//GenQueue header
#ifndef GENQUEUE
#define GENQUEUE

#include "DoublyLinkedlist.h"

#include <iostream>

using namespace std;

template <typename T>
class GenQueue {
    public:
        GenQueue(); // default constructor
        ~GenQueue(); // destructor

        // core functions
        void enqueue(T *d);
        T* dequeue();

        // aux functions
        T* peek();
        bool isEmpty();
        unsigned int getSize();

        void printQueue();

    private:
        DoublyLinkedList<T> *list; // pointer to a list of elements of type T
};

#endif

// GenQueue implementation

template <typename T>
GenQueue<T>::GenQueue() {
    list = new DoublyLinkedList<T>();
}

template <typename T>
GenQueue<T>::~GenQueue() {
    delete list;
}

template <typename T>
void GenQueue<T>::enqueue(T *d) {
    list->insertBack(d);
}

template <typename T>
T* GenQueue<T>::dequeue() {
    if(list->getSize() != 0) {
        T *data = list->removeFront();
        return data;
    }
    cout << "Queue is empty" << endl;
}

template <typename T>
T* GenQueue<T>::peek() {
    if(list->getSize() != 0)
        return list->peekFront();
    cout << "Queue is empty" << endl;
}

template <typename T>
bool GenQueue<T>::isEmpty() {
    return (list->isEmpty());
}

template <typename T>
unsigned int GenQueue<T>::getSize() {
    return (list->getSize());
}

template <typename T>
void GenQueue<T>::printQueue() {
    list->printList();
}
