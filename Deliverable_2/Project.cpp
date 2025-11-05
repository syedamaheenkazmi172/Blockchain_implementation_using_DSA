#include <iostream>
#include <fstream>
#include <unordered_map>
#include <windows.h>
#include "queue1.cpp"
using namespace std;
void banner()
{

    cout << R"(
  ____   _       ____    ____   _  __  ____   _   _      _      ___   _   _ 
 | __ ) | |     / __ \  / ___| | |/ / / ___| | | | |    / \    |_ _| | \ | |
 |  _ \ | |    | |  | || |     | ' / | |     | |_| |   / _ \    | |  |  \| |
 | |_) || |___ | |__| || |___  | . \ | |___  |  _  |  / ___ \   | |  | |\  |
 |____/ |_____| \____/  \____| |_|\_\ \____| |_| |_| /_/   \_\ |___| |_| \_|
                                                                              
)" << endl;
    cout << "=============================================================\n";
    cout << "        BLOCKCHAIN SIMULATION \n";
    cout << "=============================================================\n\n";
}
class User
{
    string priv_key = "", public_key = "", name = "";

public:
    int wallet(string usr)
    {
        fstream user;
        bool br = false;
        user.open(usr + ".txt", ios::in);
        if (!user)
        {
            cout << "User's File is missing\n";
            user.close();
            return 0;
        }
        else
        {

            user.close();
            link *head, *ptr;
            int count_of_unallocated_blocks = 0;

            while (true)
            {
                banner();
                fstream user;
                user.open(usr + ".txt", ios::in);
                string temp = "", temp1 = "";
                getline(user, temp, '|'), getline(user, temp1, '|');
                user.close();
                cout << "1.Create Transaction\t\t\t\t\t\t\t\t" << temp << "\n2.Switch to Mining account\t\t\t\t\t\t\t" << temp1 << "\n3.View Pending Queue of your Transactions\n4.View Detailed History\n5.Exit\n";
                int choice = 0;
                cout << "\nSelect choice\n";
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    if (count_of_unallocated_blocks > 0)
                    {
                        cout << "Enter your Private key for extra authentication\n";
                        string pi = "";
                        cin >> pi;
                        if (pi == priv_key)
                        {
                            cout << "Enter the Total amount you want to transfer\n";
                            double amount;
                            cin >> amount;
                            enqueue(count_of_unallocated_blocks, ptr, amount, usr);
                            count_of_unallocated_blocks++;
                        }
                        else
                        {
                            cout << "Private key doesnot match\n";
                            // return 0;
                        }
                    }
                    else
                    {
                        string pi = "";
                        cout << "Enter your Private key for extra authentication\n";
                        cin >> pi;
                        if (pi == priv_key)
                        {
                            cout << "Enter the Total amount you want to transfer\n";
                            double amount;
                            cin >> amount;
                            initial(head, ptr, amount, usr);
                            count_of_unallocated_blocks++;
                        }
                    }
                    cout << "\nRedirecting to Dashboard in 5 seconds\n";
                    Sleep(5000);
                    system("cls");
                    break;
                }
                case 3:
                {
                    cout << "The queue for pending transactions is:\n";
                    for (link *p = head; p != NULL; p = p->next)
                    {
                        cout << p->block->hash << " --> ";
                    }
                    cout << "\n";
                    break;
                }
                default:
                    cout << "Invalid choice\n";
                    br = true;
                    break;
                }
                if (br)
                {
                    break;
                }
            }
        }
        user.close();
        return 1;
    }
    void login(string usr, string priv)
    {
        fstream user_name, private_key;
        user_name.open("login.txt", ios::in);
        if (!user_name)
        {
            cout << "Couldn't find the username file\n";
            Sleep(2000);
            cout << "Locate the file and try again\n";
            return;
        }
        private_key.open("Login_p.txt", ios::in);
        if (!private_key)
        {
            cout << "Couldn't find the Private_key file\n";
            Sleep(2000);
            cout << "Locate the file and try again\n";
            return;
        }
        string *temp = new string[2];
        bool yes = false;
        while (getline(user_name, temp[0]))
        {
            cin.ignore();
            getline(private_key, temp[1]);
            if (temp[0] == usr)
            {
                if (temp[1] == priv)
                {
                    cout << "User found\n";
                    priv_key = temp[1];
                    name = temp[0];
                    for (int i = 0; i < 32; i++)
                        public_key.push_back(priv_key[i] ^ 'a');
                    yes = true;
                    // cin.ignore();
                    break;
                }
            }
            // cin.ignore();
        }
        delete[] temp;
        user_name.close();
        private_key.close();
        if (!yes)
        {
            cout << "Cannot find User\n";
        }
        else
        {
            cout << "You will be directed to your wallet in a few seconds\n";
            Sleep(2500);
            system("cls");
            wallet(usr);
        }
    }
};
int main()
{
    banner();
    cout << "Welcome, Login as a User or a Miner(U/m)\n";
    string in;
    cin >> in;
    if (in == "U")
    {
        User jh;
        cout << "Welcome Wallet user\n1.Login as existing user\n2.Signup as a new User:\n";
        int input;
        cin >> input;
        if (input == -1)
        {
            cout << "Invalid option selected\n";
        }
        else if (input == 1)
        {
            cout << "Enter your Username and Private Key to access your Wallet\n";
            string temp = "", temp1 = "";
            cin >> temp >> temp1;
            jh.login(temp, temp1);
        }
        else if (input == 2)
        {
            cout << "Signup functionality is under development\n";
        }
    }
    else if (in == "m")
    {
        cout << "Miner login is under development\n";
    }
    else
    {
        cout << "Invalid choice\n";
    }
}
