// ListNode header
#ifndef LISTNODE
#define LISTNODE

template <typename T>
class ListNode {

    public:
        ListNode();
        ListNode(T *data);
        ~ListNode();
        T *data;
        ListNode *next;
        ListNode *prev;
};

#endif

// ListNode implementation

template <typename T>
ListNode<T>::ListNode() {
    delete data;
}

template <typename T>
ListNode<T>::ListNode(T *data) {
    this->data = data;
    next = 0;
    prev = 0;
}

template <typename T>
ListNode<T>::~ListNode() {
    next = 0;
    prev = 0;
    delete data;
}
