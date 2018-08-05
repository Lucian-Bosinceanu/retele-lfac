#include <string>
#include "loginComponent.h"
#include "CommunicationComponent.h"
#define REQUEST_MAX_SIZE 256
#define RESPONSE_MAX_SIZE 1024

using namespace std;

class Server {

    private:
    string buffer;
    loginComponent* login;
    CommunicationComponent* pipeSlave;
    char* currentWorkingPath;

    char* commandList[REQUEST_MAX_SIZE];
    void prepareCommandList(char* command);

    void interpretRequest(string request);

    void runGenericCommand(string command);
    void runMyStat(string path, string fileName);
    void runMyFind(string path);

    void findFile(char directory[RESPONSE_MAX_SIZE], char pattern[REQUEST_MAX_SIZE]);

    bool isDotsDirectory(char entryName[REQUEST_MAX_SIZE]);
    bool isExpectedFile(char entryName[REQUEST_MAX_SIZE], char pattern[REQUEST_MAX_SIZE]);


    public:
    string connectToServer();
    void receiveRequestFromClient(CommunicationComponent* communication);
    string sendResponseToClient();
    char* getCurrentWorkingPath() {return currentWorkingPath;};
    bool isCdCommand(string command);
    void runChangeDirectory(string path);
    bool isQuitCommand(string command) { return command.find( string("quit") ) != std::string::npos;};

};
