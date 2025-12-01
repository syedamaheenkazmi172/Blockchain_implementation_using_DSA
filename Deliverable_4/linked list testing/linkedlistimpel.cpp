#include <iostream>
#include <string>
#include <fstream>


using namespace std;
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
};

static int amountofblocks;

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
            Block *ptr = new Block;
            update_money(am, money, user, name, rec);
            ptr->fee = money;
            ptr->fee = money;
            ptr->nonce = noncemaker();
            ptr->hash = hashmaker(ptr->nonce);

            cout << "Generated Hash: " << ptr->hash << endl;

            ptr->index = amountofblocks;
            cout << "Index number for the transaction: " << ptr->index << endl;

            amountofblocks++;

            return ptr;
        }
    }
    return NULL;
}
