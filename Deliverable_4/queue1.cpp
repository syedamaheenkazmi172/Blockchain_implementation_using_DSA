#include <iostream>
#include "linked list testing\linkedlistimpel.cpp"
using namespace std;
struct link
{
    Block *block;
    link *next = NULL;
    link *prev = NULL;
};


struct bstbch
{
    bstbch* left;
    bstbch* right;
    Block* block;
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

    cout << "Highest priority block: " << endl;
    cout << "Hash: " << temp->block->hash << "  , Fee: " << temp->block->fee << endl;
    return 0;
}

void dequeue(link* &head)
{
    if(head == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }

    link* test = head;
    head = head->next;

    delete test;
}


bstbch* bstinsert(bstbch* &chainstart, Block* block)
{
    bstbch* t;
    if(chainstart==NULL)
    {
        t = new bstbch;
        t->left = t->right = NULL;
        t->block = block;
        return t;
    }

    else if(block->fee > chainstart->block->fee)
    {
        chainstart->right = bstinsert(chainstart->right, block);
    }

    else
    {
        chainstart->left = bstinsert(chainstart->left, block);
    }

    return chainstart;
}

void bsttraversal(bstbch* chainstart)
{
    if(chainstart != NULL)
    {
        bsttraversal(chainstart->left);
        cout << chainstart->block->hash << ", " << chainstart->block->fee << endl;
        bsttraversal(chainstart->right);
    }
}
