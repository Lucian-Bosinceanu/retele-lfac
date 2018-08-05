#include "Client.h"
#include <string>
#include <iostream>
#include <string.h>
#include <sys/wait.h>
#define REQUEST_MAX_SIZE 256


using namespace std;

string Client::getRequestFromConsole() {

char request[REQUEST_MAX_SIZE];
writePrompt();
int nr;
cin.getline(request,REQUEST_MAX_SIZE);

buffer.clear();

if ( string(request).find("cd ") != std::string::npos )
    return string(request);

if ( (nr = write(communication->getWriteStream(),request,strlen(request) )) == -1 )
     perror("Client-side error - getRequestFromConsole()!\n");


return string(request);
}

void Client::promptResponseFromServer(string response) {

cout<<response<<'\n';
}

void Client::run(string communicationType) {

    server = new Server();
    int child;
    int responseLength;
    char response[RESPONSE_MAX_SIZE];

    username = server->connectToServer();
    cout<<'\n';

    communication = new CommunicationComponent(communicationType);

    while (1) {

        //communication = new CommunicationComponent(communicationType);
        buffer = getRequestFromConsole();

        if (server->isCdCommand(buffer))
            {
            server->runChangeDirectory(buffer.substr( string("cd ").length() ));
            //delete communication;
            continue;
            }

        if (server->isQuitCommand(buffer))
            {
            delete communication;
            exit(0);
            }

        if ((child = fork()) == -1) perror("Err...fork");
            else
              if (child)   //parinte
                {
                    wait(NULL);

                    if ( (responseLength = read(communication->getReadStream(), response, RESPONSE_MAX_SIZE) )< 0)
                        perror("Server-side read error - receiveRequestFromClient()!\n");

                    response[ responseLength ] = 0;

                    promptResponseFromServer( string(response));
                    //delete communication;

                }
                else     //copil
                  {
                    server->receiveRequestFromClient(communication);
                    server->sendResponseToClient();
                    exit(0);
                  }

        }

}


void Client::writePrompt() {

cout<<username<<"@command: ";
}
