#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool IsLoggedIn() {
    string username, password, un, pw;
    cout << "Enter Username: "; cin >> username;
    cout << "Enter Password: "; cin >> password;

    ifstream read("data\\" + username + ".txt");
    getline(read, un);
    getline(read, pw);

    if (un == username && pw == password){
        return true;
     } else {
        return false;
     };
}

int Main() {
    int choice;

    cout << "1: Register\n2: Login\nYour Choice:";
    cin >> choice;
}