// DoublyLinkedList header
#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

#include "ListNode.h"
#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList {

    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;

    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void insertFront(T *d);
        void insertBack(T *d);
        T* peekFront();
        T* peekBack();
        T* removeFront();
        T* removeBack();
        T* find(T *value);
        T* removePos(int pos);
        T* removeElement(T *key);

        bool isEmpty();
        unsigned int getSize();

        void printList();
};

#endif

// DoublyLinkedList implementation

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    front = NULL;
    back = NULL;
    size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    ListNode<T> *nextNode;
    while(front != NULL) {
        nextNode = front->next;
        delete front;
        front = nextNode;
    }
    nextNode = NULL;
    back = NULL;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T *d) {
    ListNode<T> *newNode = new ListNode<T>(d);
    if(size == 0) {
        back = newNode;
    } else {
        front->prev = newNode;
        newNode->next = front;
    }
    front = newNode;
    size++;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T *d) {
    ListNode<T> *newNode = new ListNode<T>(d);
    if(front == NULL) {
        back = newNode;
        front = back;
    } else {
        back->next = newNode;
        newNode->prev = back;
        back = newNode;
    }
    size++;
}

template <typename T>
T* DoublyLinkedList<T>::peekFront() {
    return front->data;
}

template <typename T>
T* DoublyLinkedList<T>::peekBack() {
    return back->data;
}

template <typename T>
T* DoublyLinkedList<T>::removeFront() {
    ListNode<T> *node = front;
    if(front->next == NULL) { // if one element
        back = NULL; // null back pointer before removing
    } else {
        front->next->prev = NULL; // null next's pointer to front
    }
    front = front->next;
    --size;
    node->next = NULL;

    return node->data;
}

template <typename T>
T* DoublyLinkedList<T>::removeBack() {
    ListNode<T> *node = back;
    if(back->prev == NULL) { // if one element
        front = NULL; // null front pointer before removing
    } else {
         back->prev->next = NULL;// null back's prev's pointer to back
    }
    back = back->prev;
    --size;
    node->prev = NULL;

    return node->data;
}

template <typename T>
T* DoublyLinkedList<T>::find(T *value) {
    int pos = -1;

    ListNode<T> *curr = front;
    while(curr != NULL) {
        pos++;
        if(curr->data == value)
            break;
        curr = curr->next;
    }
    if(curr == NULL) // if did not find value
        pos = -1;

    return pos;
}

template <typename T>
T* DoublyLinkedList<T>::removePos(int pos) {
    int p = 0;
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;

    // iterate to correct position
    while(p != pos) {
        // iterate and update my pointers
        prev = curr;
        curr = curr->next;
        p++;
    }

    // found target, all pointers should be in correct locations
    prev->next = curr->next;
    curr->next = NULL;
    T *temp = curr->data;
    size--;

    delete curr;
    return temp;
}

template <typename T>
T* DoublyLinkedList<T>::removeElement(T* key) {
    ListNode<T> *curr = front;


    // loop through list to find key/value
    while(curr->data != key) {
        curr = curr->next;

        if(curr == NULL)
            return -1;
    }

    // found node, now delete

    // check if front
    if(curr == front) {
        front = curr->next;
        front->prev = NULL;
    } else if(curr == back) {
        back = curr->prev;
        back->next = NULL;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    curr->next = NULL;
    curr->prev = NULL;

    T *ret = curr->data;
    delete curr;
    size--;

    return ret;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return (size == 0);
}

template <typename T>
unsigned int DoublyLinkedList<T>::getSize() {
    return size;
}

template <typename T>
void DoublyLinkedList<T>::printList() {
    ListNode<T> *curr = front;
    while(curr != NULL) {
        if(curr == front)
            cout << "{FRONT}: ";
        else if(curr == back)
            cout << "{REAR}: ";

        cout << "[ " << curr->data << " ] ";

        curr = curr->next;
        if(curr != NULL)
            cout << " ==> ";
    }
    cout << endl;
}
