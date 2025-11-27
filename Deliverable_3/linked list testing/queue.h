#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "linkedlistimpel.h"

using namespace std;
struct queue
{
    Block* front;
    Block* rear;

    void enqueue(Block *ptr);
    void dequeue();
    bool isEmpty();
    double getFront();
    void display();
    void dequeueById(int id);
};

extern queue txQueue;
#endif