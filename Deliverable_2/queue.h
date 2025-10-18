#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "linked list testing/linkedlistimpel.cpp"

using namespace std;
struct queue
{
    Block* front;
    Block* rear;

    void enqueue(Block *ptr);
    void dequeue();
    bool isEmpty();
    double getFront();
};

extern queue txQueue;
#endif