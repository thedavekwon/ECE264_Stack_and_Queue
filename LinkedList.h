//
// Created by Do Hyung Kwon on 11/12/18.
//

#ifndef STACKANDQUEUE_LINKEDLIST_H
#define STACKANDQUEUE_LINKEDLIST_H

#include <string>

// Template were used to perform generic programming. LinkedList contains head and tail pointers and name.
template<class T>
class LinkedList {
protected:
    // Nodes were created nested class in protected because we don't want Node to be public
    // and accessible from main function.
    class Node {
    private:
        T value;
        Node *next;

    public:
        explicit Node(T _value) {
            value = _value;
            next = nullptr;
        }

        T getValue() {
            return value;
        }

        void setNext(Node *nextNode) {
            next = nextNode;
        }

        Node *getNext() {
            return this->next;
        }
    };

    Node *head;
    Node *tail;
    std::string name;

    // virtual are used to indicate that it will be implemented differently from Stack and Queue
    // virtual are not used for functions that Stack and Queue uses same function
public:
    LinkedList();

    virtual void push(T value) {};

    void pop();

    bool checkPop();

    virtual T top() = 0;

    std::string getName();
};

// Queue and Stack only need to implement virtual functions from the LinkedList
template<class T>
class Stack : public LinkedList<T> {
public:
    explicit Stack(std::string _name);

    void push(T value);

    T top();
};

template<class T>
class Queue : public LinkedList<T> {
public:
    explicit Queue(std::string _name);

    void push(T value);

    T top();
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    name = "";
}

template<class T>
std::string LinkedList<T>::getName() {
    return this->name;
}

template<class T>
bool LinkedList<T>::checkPop() {
    return !(this->head == nullptr && this->tail == nullptr);
}

template<class T>
void LinkedList<T>::pop() {
    if (this->head == this->tail) {
        Node *tmp = this->head;
        delete tmp;
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }
    Node *tmp = this->head;
    this->head = this->head->getNext();
    delete tmp;
}

// Stack
template<class T>
Stack<T>::Stack(std::string _name) {
    this->head = nullptr;
    this->tail = nullptr;
    this->name = _name;
}

// When the Stack is empty, we have to set both head and tail to new node. Except for that edge case we can simply
// push new node and set it to be new head. tail is not really used in stack
template<class T>
void Stack<T>::push(T value) {
    class LinkedList<T>::Node *node = new class LinkedList<T>::Node(value);
    if (this->head == nullptr && this->tail == nullptr) {
        this->head = this->tail = node;
        this->head->setNext(this->tail);
        return;
    }
    node->setNext(this->head);
    this->head = node;
}

template<class T>
T Stack<T>::top() {
    return this->head->getValue();
}

template<class T>
Queue<T>::Queue(std::string _name) {
    this->head = nullptr;
    this->tail = nullptr;
    this->name = _name;
}

// When the Queue is empty, we have to set both head and tail to new node. Except for that edge case we can simply
// push new node and set it to be new tail. both head (pop) and tail (push) is used in queue.
template<class T>
void Queue<T>::push(T value) {
    class LinkedList<T>::Node *node = new class LinkedList<T>::Node(value);
    if (this->head == nullptr && this->tail == nullptr) {
        this->head = this->tail = node;
        return;
    }
    this->tail->setNext(node);
    this->tail = node;
}

template<class T>
T Queue<T>::top() {
    return this->head->getValue();
}

#endif //STACKANDQUEUE_LINKEDLIST_H
