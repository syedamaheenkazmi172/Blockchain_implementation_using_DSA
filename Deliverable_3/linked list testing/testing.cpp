#include<iostream>
#include<string>
#include<sstream>

#include "queue.h"
#include "linkedlistimpel.h"

using namespace std;

int main()
{
    Block* blk1 = transaction(20.0, "Youraj");
    Block* blk2 = transaction(15.0, "Youraj");
    Block* blk3 = transaction(30.0, "Youraj");
    mine_transaction();
    chain.saveChain();
    return 0;
}