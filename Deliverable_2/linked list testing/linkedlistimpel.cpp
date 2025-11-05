#include <iostream>
#include <string>
#include <fstream>

// #include "..\queue.h"
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
struct Block
{
    int index;
    string prevHash;
    string nonce;
    string hash;
    Block *next;

    Block *prev; // blocks are supposed to be interconnected especially as we are also considering prevHash
    double fee;
};

// THIS CLASS IS GOING TO BE IMPLEMENTED POST DELIVERABLE 2
// working with a class makes it easier to connect all the Blocks (i.e nodes) hence fullfilling the purpose of the linked list and blockchain
class BlockChain
{
private:
    Block *previous; // the second last node should always be assigned to previous
    Block *head;     // the first node should always be assigned to head

public:
    BlockChain() // CONSTRUCTOR
    {
        this->previous = NULL;
        this->head = NULL;
    }
};

static int amountofblocks; // updating index for each block

string noncemaker() // generates a 6 digit integer that can be used as a nonce
{
    srand(time(0));
    int number = rand() % 900000 + 100000;
    return to_string(number);
}

string hashmaker(string ab)
{
    // convert nonce(string) to a random value so that we can hash it
    int val = stoi(ab) * 37 + 13; // stoi is a string to integer converter

    for (int i = 0; i < 6; i++) // 6 character hash
    {
        char base = 'A' + (stoi(ab) % 10); // the first part of the hash will keep changing b/w 'A' & 'J'
        char postbase = base + (val % 26); // sample functin: A + 0-25(A-Z) = AA/AB....
        ab += postbase;                    // adds postbase to the string hash
        val = val / 3 + i * 7;             // changes the value of val for the next iteration
    }

    return ab;
}

Block *transaction(double money = 0, string name = "")
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
        am = stod(nu);
        if (am < money)
        {
            cout << "Specified Amount is more than Balance\n";
            Block *ptr;
            return ptr;
        }
        else
        {
            user.close();
            user.open(name + ".txt", ios::in);
            Block *ptr = new Block;
            update_money(am, money, user, name);
            ptr->fee = money;
            ptr->next = NULL; // new node so the next node should always be null

            ptr->prevHash = hashmaker(noncemaker()); // we dont need a previous nonce when starting the blockchain
            ptr->fee = money;
            ptr->nonce = noncemaker();
            ptr->hash = hashmaker(ptr->nonce);

            cout << "Generated Hash: " << ptr->hash << endl;

            ptr->index = amountofblocks;
            cout << "Index number for the transaction: " << ptr->index << endl;

            amountofblocks++; // has been increase as a new one has been added;

            return ptr; // function changed from void to Block* so that this function can be implemented in other files
        }
    }
    return ptr;
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