#include <string>
#include "Server.h"

using namespace std;

class Client {

    private:
    string buffer;
    string username;
    string response;
    CommunicationComponent* communication;
    Server* server;

    string getRequestFromConsole();
    void promptResponseFromServer(string response);
    void writePrompt();
    void updateCurrentWorkingPath() { chdir(server->getCurrentWorkingPath()); };

    public:
    void run(string communicationType);
};
