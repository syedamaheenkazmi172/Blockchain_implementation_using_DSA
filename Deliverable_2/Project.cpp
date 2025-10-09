#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
void login()
{
    fstream user_name, private_key;
    string usr, pivate_key;
    user_name.open("login.txt", ios::in);
    private_key.open("Login_p.txt", ios::in);
    string *temp = new string[2];
    unordered_map<string, string> users;
    while (getline(user_name, temp[0]))
    {
        getline(private_key, temp[1]);
        users[temp[0]] = temp[1];
    }
    delete[] temp;
    user_name.close();
    private_key.close();
}
void signup();
string verify_login(string input)
{
    if (input != "1" || input != "2")
    {
        return "-1";
    }
    else if (input == "1")
    {
        return "1";
    }
    else
    {
        return "2";
    }
}
int main()
{
    cout << "Welcome Wallet user\n1.Login as existing user\n2.Signup as a new User:\n";
    string input;
    cin >> input;
    string n = verify_login(input);
    if (n == "-1")
    {
        cout << "Invalid option selected\n";
    }
    else if (n == "1")
    {
        login();
    }
    else
    {
        signup();
    }

    fstream hello;
}
