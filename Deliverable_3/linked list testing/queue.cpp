#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "queue.h"

using namespace std;

queue txQueue = {NULL, NULL}; // initializing the queue
void queue::enqueue(Block *ptr)
{
    if (rear == NULL) // if the queue is empty
    {
        front = rear = ptr;
        return;
    }

    // rear->next = ptr; //linking the new node at the end of the queue
    // rear = ptr;

    // to sort the queue in descending order based on fee so that we can form a priority queue
    for (Block *i = front; i != NULL; i = i->next)
    {
        if (i->fee <= ptr->fee)
        {
            if (i == front) // inserting at the front
            {
                ptr->next = front;
                front = ptr;
            }
            else // inserting in between or at the end
            {
                Block *temp = front;
                while (temp->next != i)
                {
                    temp = temp->next;
                }
                temp->next = ptr;
                ptr->next = i;
            }
            return;
        }
    }
}

void queue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << std::endl;
        return;
    }
    Block *temp = front; // storing the previous front node

    front = front->next; // updating front to point to the next node

    if (front == NULL)
        rear = NULL;

    delete temp;
}

bool queue::isEmpty()
{
    return front == NULL;
}

double queue::getFront()
{
    if (front != NULL)
        return front->fee;
    else
        throw runtime_error("Queue is empty");
}
