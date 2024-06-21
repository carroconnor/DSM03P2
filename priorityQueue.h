#ifndef PRIORIYQUEUE_H
#define PRIORIYQUEUE_H
#include "queueADT.h"
#include "linkedList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;

template <class Type>
struct nodeType
{
    Type * info;
    nodeType<Type> *link;
    ~nodeType()
    {
        delete info;
    }
};

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
    nodeType<Type> * queueFront;
    nodeType<Type> * queueRear;
    int maxQueueSize;
    linkedListType<Type> *list;
};

template <class Type>
bool priorityQueueType<Type>::isEmptyQueue() const
{
    return queueFront == nullptr;
}

template <class Type>
bool priorityQueueType<Type>::isFullQueue() const
{
    return list->length() >= maxQueueSize;
}

template <class Type>
void priorityQueueType<Type>::initializeQueue()
{
    nodeType<Type> * current;
    
    
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
    if(isFullQueue())
    {
        throw out_of_range("Queue is full");
    }
    else
    {
        list->insertLast(queueElement);
    }
}

template <class Type>
Type priorityQueueType<Type>::dequeue()
{
    if(isEmptyQueue())
    {
        throw out_of_range("Queue is empty");
    }
    else
    {
        Type temp = list->front();
        list->deleteNode(temp);
        return temp;
    }
}

#endif