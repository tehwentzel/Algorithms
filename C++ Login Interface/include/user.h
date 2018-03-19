#ifndef USER_H
#define USER_H
#include <string>


class user{
    private:
        std::string username;
        std::string password;
        std::string email;
    public:

        bool login;
        user();
        user(std::string name, std::string mail, std::string pass);

        void set_username(std::string str);
        void set_password(std::string str);
        void set_email(std::string str);
        void log_in(std::string str);

        std::string get_email(){
            return email;
        }

        std::string get_password(){
            return password;
        }

        std::string get_username(){
            return username;
        }

        bool operator== (const user &u2){
            return (username == u2.username);
        }

        bool operator!= (const user &u2){
            return (username != u2.username);
        }

        bool operator< (const user &u2) const{
            return (username < u2.username);
        }

        void operator= (user u2){
            username = u2.get_username();
            password = u2.get_password();
            email = u2.get_email();
        }

        virtual ~user();
};

#endif // USER_H
