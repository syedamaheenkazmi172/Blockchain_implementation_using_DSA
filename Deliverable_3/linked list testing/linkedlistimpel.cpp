#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "queue.h"
#include "linkedlistimpel.h"
//  #include <SHA256.h>
using namespace std;


void update_money(double money, double amount, fstream &user, string name)
{
    string temp = "";
    getline(user, temp);
    int n = temp.size();
    for (int i = 0; temp[n - i - 2] != ':'; i++)
    {
        temp.erase(n - i - 2);
    }
    user.close();
    fstream user_out;
    user_out.open(name + ".txt", ios::out);
    temp = temp + to_string(int(money - amount));
    user_out << temp + "|";
    user_out.close();
}

BlockChain::BlockChain() // CONSTRUCTOR
{
    this->head = nullptr;
    this->tail = nullptr;
    getChain();
}

void BlockChain::getChain()
{
    ifstream infile;
    infile.open("blockchain.txt");

    if (!infile)
    {
        return; // file not found, empty chain
    }

    while (head)
    {
        // delete any existing chain in memory to free up space
        Block *tmp = head;
        head = head->next;
        delete tmp;
    }

    head = tail = nullptr; // reset chain

    string line;
    int linecount = 0;

    while (getline(infile, line))
    {
        if (line.empty())
        {
            continue;
            // move to next line
        }

        stringstream ss(line);
        Block *newblock = new Block;

        ss >> newblock->index >> newblock->prevHash >> newblock->nonce >> newblock->hash >> newblock->fee;
        insert(newblock);
        cout<<"Loaded Block " << linecount << ": " << newblock->index << " " << newblock->prevHash << " " << newblock->nonce << " " << newblock->hash << " " << newblock->fee << endl;
        linecount++;
    }
}

void BlockChain::insert(Block *ptr)
{
    ptr->next = NULL;
    ptr->prev = NULL;

    if (tail == NULL)
    { // empty chain
        head = tail = ptr;
        // genesis previous hash
        if (ptr->prevHash.empty())
            ptr->prevHash = "0";
    }
    else
    {
        tail->next = ptr;
        ptr->prev = tail;
        // set prevHash of new block to previous block's hash (overwrite if needed)
        ptr->prevHash = tail->hash;
        tail = ptr;
    }

}

void BlockChain::saveChain() const
{
    ofstream ofs("blockchain.txt", ios::trunc);
    if (!ofs) {
        cerr << "Error: couldn't open blockchain.txt for writing\n";
        return;
    }

    // format: index|prevHash|nonce|hash|fee
    for (Block* it = head; it != nullptr; it = it->next) {
        ofs << it->index << "|" << it->prevHash << "|"
            << it->nonce << "|" << it->hash << "|"
            << it->fee << "\n";
    }
    ofs.close();
    cout << "Blockchain saved to blockchain.txt\n";
    //this will store blockchain in a txt file so next time it can be loaded from there
}

BlockChain chain = BlockChain(); // global blockchain object

//static int amountofblocks; // updating index for each block

string noncemaker() // generates a 6 digit integer that can be used as a nonce
{
    srand(time(0));
    int number = rand() % 900000 + 100000;
    return to_string(number);
}

string hashmaker(string ab)
{
    int val = stoi(ab); // convert string to integer for hashing

    string finalans = ""; // final answer will be stored here

    while (val != 0)
    {
        int remainder = 0; // storing each remainder when val gets divided by 16

        char hexed; // stores the ASCII coverted form of the remainder

        remainder = val % 16;

        if (remainder < 10) // in base16, 0-9 are the same
        {
            hexed = remainder + 48; // in the ASCII table, numbers go from 48(0) to 57(9)
        }

        else
        {
            hexed = remainder + 55; // in the ASCII table, alphabets start from 65(A) so 10 + 55 = A
        }

        finalans += hexed; // updating the final answer string
        val = val / 16;    // have to divide by 16 each time
    }

    int size = finalans.size();        // we have to reverse the final answer
    for (int i = 0; i < size / 2; i++) // simple swap
    {
        char temp = finalans[size - i - 1];
        finalans[size - i - 1] = finalans[i];
        finalans[i] = temp;
    }

    return finalans;
}

Block* transaction(double money = 0, string name = "")
{
    Block *ptr;
    if (money != 0)
    {
        fstream user;
        user.open(name + ".txt", ios::in);
        string temp = "";
        double am;
        getline(user, temp);
        string nu = "";
        int n = temp.size();
        for (int i = 0; temp[n - i - 2] != ':'; i++)
        {
            nu.insert(0, 1, temp[n - i - 2]);
        }
        cout << nu << endl;
        am = stod(nu);
        if (am < money)
        {
            cout << "Specified Amount is more than Balance\n";
            user.close();
            return NULL;
        }
        else
        {
            user.close();
            user.open(name + ".txt", ios::in);
            Block *ptr = new Block;
            update_money(am, money, user, name);
            ptr->fee = money;

            // remove next and prev pointers as blocks are not being linked here, they will be linked during mining phase using BlockChain class
            // ptr->next = NULL; // new node so the next node should always be null

            ptr->prevHash = hashmaker(noncemaker()); // we dont need a previous nonce when starting the blockchain
            ptr->fee = money;
            ptr->nonce = noncemaker();
            ptr->hash = hashmaker(ptr->nonce);

            cout << "Generated Hash: " << ptr->hash << endl;

            ptr->index = amountofblocks;
            cout << "Index number for the transaction: " << ptr->index << endl;

            amountofblocks++; // has been increase as a new one has been added;

            txQueue.enqueue(ptr); // adding the new transaction to the queue
            return ptr;           // function changed from void to Block* so that this function can be implemented in other files
        }
    }
    return NULL;
}

void mine_transaction()
{
    if (txQueue.isEmpty())
    {
        cout << "No transactions to mine\n";
        return;
    }

    Block *ptr = new Block;
    ptr = nullptr;
    ptr = txQueue.front; // getting the front of the queue
    txQueue.dequeue();   // removing the transaction from the queue after mining

    chain.insert(ptr); // inserting the mined block into the blockchain
}
// //if we want to use sha256 for hashing purposes we will need to download the openssl library and make a specific function to use sha256 (too much work)

// //using a SHA256 implementation file as a header and using the functions provided in it
// void hashmaker(struct Block* ptr)
// {
//     SHA256 sha;     //object for the header file
//     sha.update(ptr->nonce);         //hashing the nonce value

//     //digest() is a function in the SHA256.h file for computing the hash
//     ptr->hash = SHA256::toString(sha.digest());     //toString() converts it into a string form
// }

// TO BE IMPLEMENTED DURING MINING PHASE (POST DELIVERABLE 2)

/*    if(previous != NULL)    //if the BlockChain is continuting
{
    previous = head;
    head = ptr;
    ptr->nonce = noncemaker();
    ptr->hash = hashmaker(ptr->nonce);

    ptr->prevHash = previous->hash;     //previous will be behind the new node

    cout << "Previous hash: " << ptr->prevHash << endl;
    cout << "Newly formed hash: " << ptr->hash << endl;

    ptr->prev = previous;   //second last node assigned previous
}

if(previous == NULL) //if the blockchain is just starting
{
    head = ptr;
    previous = head; */