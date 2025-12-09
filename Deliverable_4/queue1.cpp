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



struct stack_base
{
    double data;
    stack_base* stack_next = NULL;
};

struct history_stack
{
    stack_base* top = NULL;
    int sizeofstack;
};

stack_base* temp = new stack_base;
history_stack* obj = new history_stack;


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

string displayhash(link* &head)
{
    if(head == NULL)
    {
        cout << "No blocks have been made." << endl;
        return "";
    }

    link* temp = head;

    cout << "Highest priority block: " << endl;
    cout << "Hash: " << temp->block->hash << "  , Fee: " << temp->block->fee << endl;
    return temp->block->hash;
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
        cout << chainstart->block->hash << ", " << "Amount: " << chainstart->block->fee << endl;
        bsttraversal(chainstart->right);
    }
}


void push(double &amount)
{
    temp->data = amount;
    temp->stack_next = obj->top;
    obj->top = temp;
    (obj->sizeofstack)++;
}

int seetop()
{
    if(obj == NULL)
    {
        cout << "No recent transactions/Transaction stack empty" << endl;
        return -1;
    }

    return obj->top->data;
}