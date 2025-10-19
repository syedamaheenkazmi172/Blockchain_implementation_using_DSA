#include <iostream>
#include "linked list testing\linkedlistimpel.cpp"
using namespace std;
struct link
{
    Block *block;
    link *next = NULL;
    link *prev = NULL;
};
link *enqueue(Block *f, int i, link *p)
{
    link *s = new link;
    s->block = f;
    if (i > 1)
    {
        s->prev = p;
    }
    return s;
}
void initial(link *&head, link *&ptr, double money)
{
    head = new link;
    head->block = transaction(money);
    ptr = head;
}
void put(int i, link *&ptr, Block *block)
{
    link *s = enqueue(block, i, ptr);
    ptr->next = s;
    ptr = ptr->next;
}