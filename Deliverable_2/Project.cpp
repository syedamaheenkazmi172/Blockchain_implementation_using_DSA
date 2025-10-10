#include <iostream>
#include <fstream>
#include <unordered_map>
#include <windows.h>
using namespace std;
void banner()
/*{
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
}*/
class User
{
    string priv_key="", public_key="", name="";

public:
    int wallet(string usr)
    {
        fstream user;
        user.open(usr + ".txt", ios::in);
        if (!user)
        {
            cout << "User's File is missing\n";
            return 0;
        }
        else
        {
            banner();
            cout << "1.Create Transaction\n2.Switch to Mining account\n3.View BlockChain\n4.View all the Transactions you performed\n5.Check Balances\n5.Exit\n";
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
                    for(int i=0;i<32;i++)
                    public_key.push_back(priv_key[i]^'a');
                    yes = true;
                    //cin.ignore();
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
            cout << "Cannot found User\n";
        }
        else
        {
            cout << "You will be directed to your wallet in a few sencods\n";
            Sleep(2500);
            system("cls");
            wallet(usr);
        }
    }
    int verify_login(int input)
    {
        if (input == 2)
        {
            return 2;
        }
        else if (input == 1)
        {
            return 1;
        }
        else
        {
            return -1;
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
        int n = jh.verify_login(input);
        if (n == -1)
        {
            cout << "Invalid option selected\n";
        }
        else if (n == 1)
        {
            cout << "Enter your Username and Private Key to access your Wallet\n";
            string temp = "", temp1 = "";
            cin >> temp >> temp1;
            jh.login(temp, temp1);
        }
        else
        {
            // signup();
        }
    }
}
