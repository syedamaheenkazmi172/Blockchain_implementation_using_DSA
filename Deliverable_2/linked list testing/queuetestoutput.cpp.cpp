#include <iostream>
#include <stdexcept>
#include <algorithm>

//#include "queue.h"
#include "linkedlistimpel.cpp"

using namespace std;

struct queue
{
    Block* front;
    Block* rear;

    queue()
    {
        front = NULL;
        rear = NULL;
    }

    void enqueue(Block *ptr)
    {
        if(rear == NULL)   //if the queue is empty
        {
            front = rear = ptr;
            return;
        }

        rear->next = ptr; //linking the new node at the end of the queue
        rear = ptr;

        //to sort the queue in descending order based on fee so that we can form a priority queue
        for (Block* i = front; i != NULL; i = i->next) 
        {
            for (Block* j = i->next; j != NULL; j = j->next) 
            {
                if (i->fee < j->fee) 
                {
                    std::swap(i->fee, j->fee);
                    std::swap(i->index, j->index);
                    std::swap(i->nonce, j->nonce);
                    std::swap(i->hash, j->hash);
                    std::swap(i->prevHash, j->prevHash);
                }
            }
        }
    }

    void dequeue()
    {
        if(isEmpty())
        {
            std::cout<<"Queue is empty"<<std::endl;
            return;
        }
        Block* temp = front; //storing the previous front node

        front = front->next; //updating front to point to the next node

        if(front == NULL) 
            rear = NULL;

        delete temp; 
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    double getFront()
    {
        if(front != NULL)
            return front->fee;
        else
            throw runtime_error("Queue is empty");
    }
};

int main()
{
    double fee = 12;
    double fee2 = 13;
    Block* a = transaction(fee);
    Block* b = transaction(fee2);
    
    queue* pt = new queue;
    pt->enqueue(a);
    cout << pt->getFront() << endl;

    pt->enqueue(b);
    cout << pt->getFront();
}
