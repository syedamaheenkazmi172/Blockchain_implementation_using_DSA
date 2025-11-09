#include <iostream>
#include "linked list testing\linkedlistimpel.cpp"
using namespace std;
struct link
{
    Block *block;
    link *next = NULL;
    link *prev = NULL;
};
/*link *enqueue(Block *f, int i, link *p)
{
    link *s = new link;
    s->block = f;
    if (i > 1)
    {
        s->prev = p;
    }
    return s;
}*/
void initial(link *&head, link *&ptr, double money, string name)
{
    head = new link;
    head->block = transaction(money, name);
    ptr = head;
}
void enqueue(int i, link *&ptr, double money, string name)
{
    link *temp = ptr;
    ptr->next = new link;
    ptr = ptr->next;
    ptr->block = transaction(money, name);
    if (i > 1)
    {
        ptr->prev = temp;
    }
}