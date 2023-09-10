#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getPassword() {
    string password;
    unsigned char ch=0;
    const char BACKSPACE=127;
    const char RETURN=10;

    if ((ch=getch()) == RETURN) ch=0;

    while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
        {
            if(password.length()!=0)
            {
                cout <<"\b \b";
                password.resize(password.length()-1);
            }
        } else {
            password+=ch;
            cout <<'*';
        }
    }
    cout << endl;
    return password;
}

bool IsLoggedIn() {
    string username, password, un, pw;

    cout << "Enter Username: "; cin >> username;
    cout << "Enter Password: ";

    password = getPassword();

    ifstream read(".\\" + username + ".txt");
    getline(read, un);
    getline(read, pw);

    if (un == username && pw == password){
        return true;
     } else {
        return false;
     };
}

int main() {
    int choice;

    cout << "1: Register\n2: Login\nYour Choice: ";
    cin >> choice;

    if (choice == 1) {
        string username, password;

        cout << "Select a username: "; cin >> username;
        cout << "Select a password: ";

        password = getPassword();

        ofstream file;
        file.open(".\\" + username + ".txt");
        file << username << endl << password;
        file.close();

        main();
    } else if (choice == 2) {
        bool status = IsLoggedIn();
        if (!status) {
            cout << "False Login!" << endl;
            return 0;
        } else {
            cout << "You are succefully logged in" << endl;
            return 1;
        };

    }
    return 0;
}