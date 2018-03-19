#include "user.h"
#include <iostream>
#include <string>

user::user(){}

user::user(std::string name, std::string mail = " ", std::string pass = " "){
    username = name;
    password = pass;
    email = mail;
}

    void user::set_username(std::string str){
            username = str;
        };

void user::set_password(std::string str){
            password = str;
        };

void user::set_email(std::string str){
            email = str;
        };

void user::log_in(std::string pass){
    if(pass == password){
        login = true;
        std::cout << "Hello " << username << ", you are now logged in." << std::endl;
    }
    else{
        login = false;
        std::cout << "I'm sorry " << username << " that password isn't correct." << std::endl;
    }
}

user::~user()
{
    //dtor
}
