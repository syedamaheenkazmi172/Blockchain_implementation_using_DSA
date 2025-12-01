#include <iostream>
#include <fstream>
#include <unordered_map>
#include <windows.h>
#include "queue1.cpp"
#include <bitset>
#include <ctime>
using namespace std;

link *head, *ptr;

string private_key_maker(string name_salt)
{
    bitset<96> nu_64;
    int size = name_salt.length();
    int pos = 95;
    for (int i = 0; i < size; i++)
    {
        bitset<8> temp(name_salt[i]);
        for (int j = 7; j >= 0; j--)
        {
            nu_64[pos] = temp[j];
            pos--;
        }
    }
    string private_key = "";
    pos = 95;
    for (int i = 0; i < 16; i++)
    {
        unsigned long temp;
        bitset<6> y;
        for (int j = 5; j >= 0; j--)
        {
            y[j] = nu_64[pos];
            pos--;
        }
        temp = y.to_ullong();
        if (temp < 26)
        {
            private_key += char(temp + 65);
        }
        else if (temp >= 26 && temp < 52)
        {
            private_key += char((temp % 26) + 97);
        }
        else if (temp >= 52 && temp < 62)
        {
            private_key += char((temp % 10) + 48);
        }
        else if (temp == 62)
        {
            private_key += "/";
        }
        else
        {
            private_key += "+";
        }
    }
    return private_key;
}
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

class Miner
{

    string priv_key = "", public_key = "", name = "";

public:
    int mining(string usr)
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
            unordered_map<string, string> users_and_wallet;
            fstream users_wallet;
            users_wallet.open("users and wallet.txt", ios::in);
            string temp, temp1;
            while (getline(users_wallet, temp))
            {
                getline(users_wallet, temp1);
                users_and_wallet.insert({temp, temp1});
            }
            users_wallet.close();
            user.close();
            // link *head, *ptr;
            int count_of_unallocated_blocks = 0;
            while (true)
            {
                banner();
                fstream user;
                user.open(usr + ".txt", ios::in);
                string temp = "", temp1 = "", temp3 = "";
                getline(user, temp, '|'), getline(user, temp1), getline(user, temp3);
                int n = temp1.size();
                temp1.erase(n - 1);
                user.close();
                cout << "1.Mining\t\t\t\t\t\t\t\t" << temp << "\n2.Mining History\t\t\t\t\t\t\t" << temp1 << endl;
                int choice = 0;
                cout << "\nSelect any option:\n";
                cin >> choice;
                switch(choice)
                {
                    case 1:
                    cout << "Hashes of all the blocks present within the BlockChain: " << endl;
                    int check = displayhash(head);

                    if(check == 1)
                    {
                        cout << "You will be directed back to the miner dashboard in a few seconds\n";
                        Sleep(5000);
                        system("cls");
                        break;   
                    }

                    else
                    {
                        cout << "Please select the block which you would like to mine: " << endl;
                        string hsh;
                        cin >> hsh;

                        cout << endl;
                        

                        double giftprize = 0;
                        link* temp = head;
                        while(temp != NULL)
                        {
                            if(temp->block->hash == hsh)
                            {
                                giftprize = ((temp->block->fee)/100) * 20;
                            }

                            temp = temp->next;
                        }
                        
                        cout << "Starting the mining process......" << endl;
                        Sleep(5000);
                        for(int i = 1000; i<=9000; i++)
                        {
                            string strto = to_string(i);
                            string test = hashmaker(strto);

                            if(test == hsh)
                            {
                                cout << "Congratulations! Block " << test << " mined successfully!" << endl;
                                break; 
                            }
                        }

                        cout << "Transferring " << giftprize << " to your wallet......." << endl;
                        mining_gift(giftprize, usr);


                        cout << "You will be directed back to the miner dashboard in a few seconds\n";
                        Sleep(5000);
                        system("cls");
                        break;
                    }

                }
            }
        }
    }

    void mlogin(string usr, string priv)
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
            //cin.ignore();
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
                    break;
                }
            }
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
            cout << "You will be directed to your mining account in a few seconds\n";
            Sleep(2500);
            system("cls");
            mining(usr);
        }
    }
};

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
            unordered_map<string, string> users_and_wallet;
            fstream users_wallet("users_and_wallet.txt", ios::in);
            if (!users_wallet.is_open())
            {
                cout << "Cannot open users_and_wallet.txt\n";
                return 0;
            }

            string temp, temp1;
            while (getline(users_wallet, temp) && getline(users_wallet, temp1))
            {
                users_and_wallet.insert({temp1, temp});
            }
            users_wallet.close();

            user.close();
            // link *head, *ptr;
            int count_of_unallocated_blocks = 0;
            while (true)
            {
                banner();
                fstream user;
                user.open(usr + ".txt", ios::in);
                string temp = "", temp1 = "", temp3 = "";
                getline(user, temp, '|'), getline(user, temp1), getline(user, temp3);
                int n = temp1.size();
                temp1.erase(n - 1);
                user.close();
                cout << "1.Create Transaction\t\t\t\t\t\t\t\t" << temp << "\n2.Switch to Mining account\t\t\t\t\t\t\t" << temp1 << "\n3.View Pending Queue of your Transactions\t\t\t\t\t" << temp3 << "\n4.View Detailed History\n5.Exit\n";
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
                            cout << "Enter the wallet address of the receipent\n";
                            string wall;
                            cin >> wall;
                            try
                            {

                                string username = users_and_wallet.at(wall);
                                for (const auto &pair : users_and_wallet)
                                {
                                    cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
                                }
                                cout << "Enter the Total amount you want to transfer to " << username << "\n";
                                double amount;
                                cin >> amount;
                                enqueue(head, ptr, amount, usr, username);
                                count_of_unallocated_blocks++;
                            }
                            catch (const out_of_range &e)
                            {
                                cout << "No legitimate Such Public key exists\n";
                            }
                        }
                        else
                        {
                            cout << "Private key doesnot match\n";
                            Sleep(3000);
                            system("cls");
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
                            cout << "Enter the wallet address of the receipent\n";
                            string wall;
                            cin >> wall;
                            try
                            {
                                string username = users_and_wallet.at(wall);
                                for (const auto &pair : users_and_wallet)
                                {
                                    cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
                                }
                                cout << "Enter the Total amount you want to transfer to " << username << "\n";
                                double amount;
                                cin >> amount;
                                initial(head, ptr, amount, usr, username);
                                count_of_unallocated_blocks++;
                            }
                            catch (const out_of_range &e)
                            {
                                cout << "No legitimate Such Public key exists\n";
                            }
                        }
                    }
                    cout << "\nRedirecting to Dashboard in 5 seconds\n";
                    Sleep(5000);
                    system("cls");
                    break;
                }

                case 2:
                {    
                    cout << "Switching to your mining account.....\n";
                    Sleep(5000);
                    return 2;
                }

                case 3:
                {
                    cout << "The queue for pending transactions is:\n";
                    for (link *p = head; p != NULL; p = p->next)
                    {
                        cout << p->block->hash << " --> ";
                    }
                    cout << "\n";
                    Sleep(10000);
                    system("cls");
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
                    break;
                }
            }
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
            int store = wallet(usr);

            if(store == 2)
            {
                system("cls");
                Miner mn;
                mn.mining(usr);
            }
        }
    }
};
void sign_up()
{
y:
    fstream insert_new_user, insert_new_private_key;
    insert_new_user.open("login.txt", ios::app);
    insert_new_private_key.open("login_p.txt", ios::app);
    string username;
    cout << "Add your username\n";
    cin >> username;
    fstream log;
    log.open("login.txt", ios::in);
    string temp;
    while (getline(log, temp))
    {
        if (temp == username)
        {
            cout << "Username already taken, choose another\n";
            Sleep(3000);
            system("cls");
            banner();
            log.close();
            insert_new_private_key.close();
            insert_new_user.close();
            goto y;
        }
    }
    srand(time(0));
    int salt = rand() % 10000;
    string private_key = private_key_maker(username + to_string(salt));
    cout << "\nYour generated Private_key is: " << private_key << "\nStore this key somewhere as you will be shown this private key only once\nPress any key+Enter key to continue\n"
         << endl;
    string wallet_address = "";
    int n = rand() % 26;
    int n_1 = rand() % 10;
    for (int i = 0; i < private_key.size(); i++)
    {
        if ((private_key[i] >= 'A' && private_key[i] <= 'Z'))
        {
            if (char(n) + private_key[i] > 'Z')
            {
                wallet_address.push_back(char((private_key[i] + char(n)) % 'Z') + 'A');
            }
            else
                wallet_address.push_back(private_key[i] + char(n));
        }
        else if ((private_key[i] >= 'a' && private_key[i] <= 'z'))
        {
            if (char(n) + private_key[i] > 'z')
            {
                wallet_address.push_back(char((private_key[i] + char(n)) % 'z') + 'a');
            }
            else
            {
                wallet_address.push_back(private_key[i] + char(n));
            }
        }
        else
        {
            if (char(n_1) + private_key[i] > '9')
            {
                wallet_address.push_back(char((private_key[i] + char(n_1)) % '9') + '0');
            }
            else
                wallet_address.push_back(private_key[i] + char(n_1));
        }
    }
    char c;
    cin >> c;
    if (c)
    {
        insert_new_private_key << private_key + "\n";
        insert_new_user << username + "\n";
        insert_new_private_key.close();
        log.close();
        fstream create_user_file, users_wallet;
        users_wallet.open("users and wallet.txt", ios::app);
        create_user_file.open(username + ".txt", ios::out);
        create_user_file << "Wallet Owner:" << username << "|Current Coins:0|" << '\n'
                         << "Wallet address:" << wallet_address;
        insert_new_user.close();
        users_wallet << username << '\n'
                     << wallet_address << '\n';
        users_wallet.close();
    }
}


int main()
{
u:
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
            sign_up();
            system("cls");
            goto u;
        }
    }
    else if (in == "m")
    {
        Miner jj;
        cout << "Welcome Miner user \n1. Login as existing miner\n2. Signup as a new miner\n";
        int inp;
        cin >> inp;
        if (inp == -1)
        {
            cout << "Invalid option selected" << endl;
        }

        else if(inp == 1)
        {
            cout << "Enter your username and private key to access your mining account\n";
            string temp = "";
            string temp1 = "";
            cin >> temp >> temp1;
            jj.mlogin(temp, temp1);
        }
        else if (inp == 2)
        {
            sign_up();
            system("cls");
            goto u;
        }
    }
    else
    {
        cout << "Invalid choice\n";
    }
}
