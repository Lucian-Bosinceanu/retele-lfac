#include <string>
#include <vector>
#define COMMAND_MAX_SIZE 128

using namespace std;

class loginComponent {

    private:
    vector<string> userDatabase;
    string activeUser;
    bool userIsLoggedIn;

    bool checkUser(string user);
    void closeProgram();

    public:
    loginComponent();
    ~loginComponent();

    void interpret(string command);

    string getActiveUser() {return activeUser;}
    bool isUserLoggedIn() {return userIsLoggedIn;}
};
