#ifndef PRIORIYQUEUE_H
#define PRIORIYQUEUE_H
#include "queueADT.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;

template <class Type>
struct nodeType
{
	Type * info;
	nodeType<Type> *link;
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
    nodeType<Type> * queueFront; //front element
    nodeType<Type> * queueRear; //back element
    int maxQueueSize;
    int currentSize;
};

template <class Type>
priorityQueueType<Type>::priorityQueueType()
{
    //initialize values
    queueFront = nullptr;
    queueRear = nullptr;
    maxQueueSize = 100;
    currentSize = 0;
}

template <class Type>
priorityQueueType<Type>::priorityQueueType(const priorityQueueType<Type>& other)
{
    //copy queue
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
    //reset all nodes
    nodeType<Type> * current;
    
    while(queueFront != nullptr)
    {
        current = queueFront;
        queueFront = queueFront->link;
        delete current;
    }
    queueRear = nullptr;
}

//get the front element
template <class Type>
Type priorityQueueType<Type>::front() const
{
    return *(queueFront->info);
}

//get the back element
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
    
    //create new node
    nodeType<Type> *newNode = new nodeType<Type>;
    newNode->info = new Type(queueElement);
    newNode->link = nullptr;

    //if queue is empty, set front and rear to new node
    if(queueFront == nullptr){
        queueFront = newNode;
        queueRear = newNode;
    } else {
        nodeType<Type> *current = queueFront; //keep track of current, start with front
        nodeType<Type> *previous = nullptr;

        //update list based on priority, higher priority is closer to front
        while (current != nullptr && current->info->getPriority() >= queueElement.getPriority()) {
            previous = current;
            current = current->link;
        }
        //if previous is null, new node is highest priority
        if (previous == nullptr) {
            newNode->link = queueFront;
            queueFront = newNode;
        } else {
            //insert new node between previous and current
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

    nodeType<Type> *temp = queueFront;
    Type frontElement = *(queueFront->info); //get what will be the front element
    queueFront = queueFront->link; //move front to next element

    if (queueFront == nullptr) {
        queueRear = nullptr;
    }

    //delete temp node
    delete temp->info;
    delete temp;
    currentSize--;

    return frontElement;
}

#endif