#include<iostream>
#include<string>
#include<sstream>

#include "queue.h"
#include "linkedlistimpel.h"

using namespace std;

int main()
{
    // Creating some blocks to test the queue
    Block* block1 =transaction(10.5, "Youraj");
    Block* block2 =transaction(20.0, "Youraj");
    Block* block3 =transaction(15.0, "Youraj");

    txQueue.display();
    mine_transaction(block1->index);
    chain.saveChain();
    return 0;
}