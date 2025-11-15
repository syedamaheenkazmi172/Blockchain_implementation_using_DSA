#ifndef LINKEDLISTIMPEL_H
#define LINKEDLISTIMPEL_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//#include "queue.h"

using namespace std;

struct Block
{
    int index;
    string prevHash;
    string nonce;
    string hash;
    Block *next;    // added
    Block *prev;    // added
    double fee;
};

class BlockChain
{
private:
    Block *head; // first block
    Block *tail; // last block
public:
    BlockChain(); // CONSTRUCTOR
    void getChain();

    void insert(Block* ptr);
};

extern BlockChain chain;

static int amountofblocks; // updating index for each block

void update_money(double money, double amount, fstream &user, string name);
string noncemaker(); // generates a 6 digit integer that can be used as a nonce
string hashmaker(string nonce); // generates a hash from the nonce
void mine_transaction(); // mines the transaction at the front of the txQueue and adds it to the blockchain
void transaction(double money, string name); // creates a new transaction block and adds it to the txQueue

#endif