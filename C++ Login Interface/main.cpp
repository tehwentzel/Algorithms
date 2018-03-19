#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "user.h"

using namespace std;

void dataEntry(ifstream &file, set<user> &database){
    string newline;

    while(getline(file, newline)){
        user newuser;
        newuser.set_username(newline);
        getline(file, newline);
        newuser.set_email(newline);
        getline(file, newline);
        newuser.set_password(newline);
        database.insert(newuser);
    }

}

void updatePasswords(fstream &fileout, set<user> database){
    for(auto x: database){
        fileout << x.get_username() << "\n";
        fileout << x.get_email() << "\n";
        fileout << x.get_password() << "\n";
    }
}

void login_script(){
    cout << "Options:\n1 - Log on or change user\n2 - Change password\n3 - Update e-mail\n4 - Display info\n5 - Create new account\n6 - Quit" << endl;
}

void Option1(const string &str, user &current, set<user> database){
    user found_user;

    for(auto x: database){
        if(x.get_username() == str){
            found_user = x;
            cout << x.get_username();
        }
    }

    if(found_user.get_username() == ""){
        cout << "Username not found" << endl;
        return;
    }

    else{
        string passcode;
        cout << "enter the password: ";
        cin >> passcode;
        if(passcode == found_user.get_password()){
            current = found_user;
            cout << "Hello " << current.get_username() << ", you are now online" << endl;
            return;
        }
    }
}

int main()
{
    ifstream file("password.txt");

    set<user> database;

    dataEntry(file, database);

    user jeff;
    jeff.set_username("jeff");
    jeff.set_email("jeff@loljk.io");
    jeff.set_password("jorell");
    database.insert(jeff);

    file.close();

    int choice = 0;
    user currentuser;

    while(choice != 6){
        login_script();
        cin >> choice;
        switch(choice){

        case 1: {
                string input;
                cout << "Enter a username: ";
                cin >> input;
                Option1(input, currentuser, database);
                cout << endl;
                break;
        }

        case 2: {
            if(currentuser.get_username() == ""){
                cout << "You must log on first" << endl;
                break;
            }
            string passcode;
            cout << "Enter current password: ";
            cin >> passcode;
            if(currentuser.get_password() != passcode){
                cout << endl << "error, is not password dude" << endl;
            }
            if(currentuser.get_password() == passcode){
                cout << endl << "enter new password: ";
                cin >> passcode;
                currentuser.set_password(passcode);
                cout << endl << "you're new password is " << currentuser.get_password() << endl;
            }
            break;
        }

        case 3: {
            if(currentuser.get_username() == ""){
                cout << "You must log on first" << endl;
                break;
            }
            string email;
            string passcode;
            cout << "Enter current password: ";
            cin >> passcode;
            if(currentuser.get_password() != passcode){
                cout << endl << "error, is not password dude" << endl;
            }
            if(currentuser.get_password() == passcode){
                cout << endl << "enter new email: ";
                cin >> email;
                currentuser.set_email(email);
                cout << endl << "you're new email is " << currentuser.get_email() << endl;
            }
            break;
        }

        case 4: {
            if(currentuser.get_username() == ""){
                cout << "You must log on first" << endl;
                break;
            }
            else{
                cout << "Username: " << currentuser.get_username() << endl;
                cout << "Email: " << currentuser.get_email() << endl;
                cout << "Password: " << currentuser.get_password() << endl;
            }
            break;
        }

        case 5: {
            string name;
            string pass;
            string mail;
            cout << "Enter username: ";
            cin >> name;
            cout << endl << "Enter email: ";
            cin >> mail;
            cout << endl << "Enter password: ";
            cin >> pass;
            user newuser(name, mail, pass);
            currentuser = newuser;
            break;
        }

        case 6: cout << "Exiting..." << endl;
                break;

        default: cout << "Invalid Input" << endl;
                break;
        }
        auto loc = database.find(currentuser);
        if(loc != database.end())
            database.erase(loc);
        database.insert(currentuser);
    }

    fstream fileout("password.txt", ios::out | ios::trunc);

    updatePasswords(fileout, database);

    fileout.close();
}
