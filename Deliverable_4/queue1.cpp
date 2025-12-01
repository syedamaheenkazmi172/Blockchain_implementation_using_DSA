#include <iostream>
#include "linked list testing\linkedlistimpel.cpp"
using namespace std;
struct link
{
    Block *block;
    link *next = NULL;
    link *prev = NULL;
};

void initial(link *&head, link *&ptr, double money, string name,string rec)
{
    head = new link;
    head->block = transaction(money, name,rec);
    ptr = head;
}
void enqueue(link *&head, link *&ptr, double money, string name,string rec)
{
    Block *newBlock = transaction(money, name,rec);
    link *node = new link;
    node->block = newBlock;
    node->next = NULL;
    node->prev = NULL;

    if (newBlock->fee > head->block->fee) {
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }
    link *p = head;
    while (p->next != NULL && p->next->block->fee >= newBlock->fee) {
        p = p->next;
    }

    node->next = p->next;
    node->prev = p;

    if (p->next != NULL) {
        p->next->prev = node;
    }

    p->next = node;
    ptr = node;
}


int displayhash(link* &head)
{
    if(head == NULL)
    {
        cout << "No blocks have been made." << endl;
        return 1;
    }

    link* temp = head;

    cout << "All hashes: " << endl;
    while(temp != NULL)
    {
        cout << "Hash: " << temp->block->hash << "  , Fee: " << temp->block->fee << endl;
        temp = temp->next;
    }

    return 0;
}
