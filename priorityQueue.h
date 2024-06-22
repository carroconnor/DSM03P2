#ifndef PRIORIYQUEUE_H
#define PRIORIYQUEUE_H
#include "queueADT.h"
#include "linkedList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;

template <class Type>
class priorityQueueType: public queueADT<Type>
{
public:
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    Type front() const;
    Type back() const;
    void enqueue(const Type& queueElement);
    Type dequeue();
    const priorityQueueType<Type>& operator= (const priorityQueueType<Type>&);
    priorityQueueType();
    priorityQueueType(const priorityQueueType<Type>&);
    ~priorityQueueType();
private:
    node<Type> * queueFront;
    node<Type> * queueRear;
    int maxQueueSize;
    int currentSize;
};

template <class Type>
priorityQueueType<Type>::priorityQueueType()
{
    queueFront = nullptr;
    queueRear = nullptr;
    maxQueueSize = 100;
    currentSize = 0;
}

template <class Type>
priorityQueueType<Type>::priorityQueueType(const priorityQueueType<Type>& other)
{
    queueFront = nullptr;
    queueRear = nullptr;
    maxQueueSize = other.maxQueueSize;
    currentSize = other.currentSize;
    copyQueue(other);
}

template <class Type>
priorityQueueType<Type>::~priorityQueueType()
{
    initializeQueue();
}

template <class Type>
bool priorityQueueType<Type>::isEmptyQueue() const
{
    return queueFront == nullptr;
}

template <class Type>
bool priorityQueueType<Type>::isFullQueue() const
{
    return currentSize >= maxQueueSize;
}

template <class Type>
void priorityQueueType<Type>::initializeQueue()
{
    node<Type> * current;
    
    
    while(queueFront != nullptr)
    {
        current = queueFront;
        queueFront = queueFront->link;
        delete current;
    }
    queueRear = nullptr;
}

template <class Type>
Type priorityQueueType<Type>::front() const
{
    return *(queueFront->info);
}

template <class Type>
Type priorityQueueType<Type>::back() const
{
    return *(queueRear->info);
}

template <class Type>
void priorityQueueType<Type>::enqueue(const Type& queueElement)
{
    if (isFullQueue()) {
        throw out_of_range("Queue is full");
    }
    
    node<Type> *newNode = new node<Type>;
    newNode->info = new Type(queueElement);
    newNode->link = nullptr;

    if(queueFront == nullptr){
        queueFront = newNode;
        queueRear = newNode;
    } else {
        node<Type> *current = queueFront;
        node<Type> *previous = nullptr;

        while (current != nullptr && current->info->getPriority() >= queueElement.getPriority()) {
            previous = current;
            current = current->link;
        }

        if (previous == nullptr) {
            newNode->link = queueFront;
            queueFront = newNode;
        } else {
            previous->link = newNode;
            newNode->link = current;

            if (current == nullptr) {
                queueRear = newNode;
            }
        }
    }

    currentSize++;
}

template <class Type>
Type priorityQueueType<Type>::dequeue()
{
    if (isEmptyQueue()) {
        throw out_of_range("Queue is empty");
    }

    node<Type> *temp = queueFront;
    Type frontElement = *(queueFront->info);
    queueFront = queueFront->link;

    if (queueFront == nullptr) {
        queueRear = nullptr;
    }

    //delete temp->info;
    delete temp;
    currentSize--;

    return frontElement;
}

#endif