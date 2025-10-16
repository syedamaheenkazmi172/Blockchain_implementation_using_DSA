#include <iostream>
#include "linked list testing/linkedlistimpel.cpp"

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

    void enqueue(double money)
    {
        Block* ptr = new Block;
        ptr->fee = money;
        ptr->next = NULL;

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
                    swap(i->fee, j->fee);
                    swap(i->index, j->index);
                    swap(i->nonce, j->nonce);
                    swap(i->hash, j->hash);
                    swap(i->prevHash, j->prevHash);
                }
            }
        }
    }

    void dequeue()
    {
        if(isEmpty())
        {
            cout<<"Queue is empty"<<endl;
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
