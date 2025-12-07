#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "../graph.h"
using namespace std;

static int amountofblocks = 0;

void update_money(double money, double amount, fstream &user, string name, string rec)
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
    fstream rec_out;
    rec_out.open(rec + ".txt", ios::in);
    getline(rec_out, temp);
    rec_out.close();
    n = temp.size();
    string k = "";
    for (int i = 0; temp[n - i - 2] != ':'; i++)
    {
        k.insert(0, 1, temp[n - i - 2]);
        temp.erase(n - i - 2);
    }
    int updated_money = stoi(k) + amount;
    temp = temp + to_string(updated_money);
    rec_out.open(rec + ".txt", ios::out);
    rec_out << temp << "|";
    rec_out.close();
}

void mining_gift(double amount, string name)
{
    fstream user;
    user.open(name + ".txt", ios::in);
    if (!user.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    string temp = "";
    getline(user, temp);
    user.close();

    int n = temp.size();
    string nu = "";

    int start = temp.rfind(':');

    for (int i = 0; temp[start + 1 + i] != '|'; i++)
    {
        nu += temp[start + 1 + i];
    }

    double money = stod(nu);

    money += amount;

    temp.erase(start + 1, nu.size());
    temp.insert(start + 1, to_string((int)money));

    fstream user_out;
    user_out.open(name + ".txt", ios::out);
    user_out << temp;
    user_out.close();
}

struct Block
{
    int index;
    string nonce;
    string hash;
    double fee;
    string prevHash;
    Block *next = NULL;
    Block *prev = NULL;
};
struct Blockchain
{
    Block *head;
    Block *tail;

    Blockchain()
    {
        this->head = nullptr;
        this->tail = nullptr;
        getChain();
    }

    void insert(Block *ptr)
    {
        ptr->next = NULL;
        ptr->prev = NULL;

        if (tail == NULL)
        {
            head = tail = ptr;
            if (ptr->prevHash.empty())
                ptr->prevHash = "0";
        }
        else
        {
            tail->next = ptr;
            ptr->prev = tail;

            if (ptr->prevHash.empty())
            {
                ptr->prevHash = tail->hash;
            }

            tail = ptr;
        }
    }

    void getChain()
    {
        ifstream block_chain;
        block_chain.open("blockchain.txt");

        if (!block_chain)
            return;
        while (head)
        {
            Block *tmp = head;
            head = head->next;
            delete tmp;
        }

        head = tail = nullptr;

        string line;
        int max_index = -1;

        while (getline(block_chain, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string id, prevHash, nonce, hash, feeStr;
            getline(ss, id, '|');
            getline(ss, prevHash, '|');
            getline(ss, nonce, '|');
            getline(ss, hash, '|');
            getline(ss, feeStr, '|');

            Block *newblock = new Block;
            newblock->index = stoi(id);
            newblock->prevHash = prevHash;
            newblock->nonce = nonce;
            newblock->hash = hash;
            newblock->fee = stod(feeStr);
            if (newblock->index > max_index)
            {
                max_index = newblock->index;
            }

            insert(newblock);
        }
        if (max_index != -1)
        {
            amountofblocks = max_index + 1;
        }

        cout << "Loaded blockchain. Next Block Index: " << amountofblocks << "\n";
        block_chain.close();
    }

    void saveChain() const
    {
        ofstream ofs("blockchain.txt", ios::trunc);
        if (!ofs)
        {
            cout << "Error: couldn't open blockchain.txt for writing\n";
            return;
        }

        for (Block *i = head; i != nullptr; i = i->next)
        {
            ofs << i->index << "|" << i->prevHash << "|" << i->nonce << "|" << i->hash << "|" << i->fee << "\n";
        }
        ofs.close();
        cout << "Blockchain saved to blockchain.txt\n";
    }


    
    void displayChain()
    {
        if (head == NULL)
        {
            cout << "Blockchain is empty.\n";
            return;
        }

        Block *temp = head;
        while (temp != NULL)
        {
            cout << temp->hash;
            temp = temp->next;
            if (temp != NULL)
            {
                cout << "->";
            }
        }
        
    }
};

string noncemaker()
{
    srand(time(0));
    int number = rand() % 9000 + 1000;
    return to_string(number);
}

string hashmaker(string ab)
{
    int val = stoi(ab);

    string finalans = "";

    while (val != 0)
    {
        int remainder = 0;

        char hexed;

        remainder = val % 16;

        if (remainder < 10)
        {
            hexed = remainder + 48;
        }

        else
        {
            hexed = remainder + 55;
        }

        finalans += hexed;
        val = val / 16;
    }

    int size = finalans.size();
    for (int i = 0; i < size / 2; i++)
    {
        char temp = finalans[size - i - 1];
        finalans[size - i - 1] = finalans[i];
        finalans[i] = temp;
    }

    return finalans;
}

Block *transaction(double money = 0, string name = "", string rec = "")
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
            ptr = new Block;
            update_money(am, money, user, name, rec);
            ptr->fee = money;
            ptr->fee = money;
            ptr->nonce = noncemaker();
            ptr->hash = hashmaker(ptr->nonce);

            cout << "Generated Hash: " << ptr->hash << endl;

            ptr->index = amountofblocks;
            cout << "Index number for the transaction: " << ptr->index << endl;

            amountofblocks++;
            addEdge(name, rec, money, false);
            saveGraph("graph.txt");
            return ptr;
        }
    }
    return NULL;
}
