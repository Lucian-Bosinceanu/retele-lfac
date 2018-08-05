#include "loginComponent.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

ifstream fin("userDatabase.txt");

loginComponent::loginComponent(){

int i, userCount;
string user;

fin>>userCount;

for (i=1;i<=userCount;i++)
    {
    fin>>user;
    userDatabase.push_back(user);
    }

userIsLoggedIn = false;
string activeUser = "";

fin.close();
}

void loginComponent::interpret(string command){

string username;
string loginCommand("login ");

if (command.compare("quit") == 0)
    closeProgram();

if (command.find(loginCommand) != std::string::npos){

    username = command.substr( loginCommand.length() );
    if ( checkUser(username) )
        {
        activeUser = username;
        userIsLoggedIn = true;
        }
    }

}

loginComponent::~loginComponent(){
userDatabase.clear();
}


bool loginComponent::checkUser(string user){

for (auto it : userDatabase)
    if ( user.compare(it) == 0)
        return true;

return false;

}

void loginComponent::closeProgram(){
exit(0);
}
