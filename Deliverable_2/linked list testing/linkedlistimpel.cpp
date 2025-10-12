#include <iostream>
#include <string>
#include <SHA256.h>
using namespace std;

struct Block {
    int index;
    string prevHash;
    string nonce;
    string hash;
    Block* next;
    double fee;
};

void noncemaker(struct Block* ptr)
{
    srand(time(0));
    int number = rand() % 900000 + 100000;
    ptr->nonce = to_string(number);
}


//if we want to use sha256 for hashing purposes we will need to download the openssl library and make a specific function to use sha256 (too much work)

//using a SHA256 implementation file as a header and using the functions provided in it
void hashmaker(struct Block* ptr)
{
    SHA256 sha;     //object for the header file
    sha.update(ptr->nonce);         //hashing the nonce value

    //digest() is a function in the SHA256.h file for computing the hash
    ptr->hash = SHA256::toString(sha.digest());     //toString() converts it into a string form                                               
}

void transaction(struct Block* ptr){};