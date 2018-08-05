#include "Server.h"
#include <string>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

using namespace std;


string Server::connectToServer() {

login = new loginComponent();

string command;
char input[COMMAND_MAX_SIZE];

while (1)
    {
     cout<<"Please login: ";
     cin.getline(input,COMMAND_MAX_SIZE);
     command = string(input);
     login->interpret(command);
     if (login->isUserLoggedIn())
        {cout<<"\n Welcome, "<<login->getActiveUser()<<"!\n";
         return login->getActiveUser();
        }
        else
        cout<<"Login failed! Invalid command or username. Use command: login <username>\n";
    }

return "";
}

void Server::receiveRequestFromClient(CommunicationComponent* communication){

char request[REQUEST_MAX_SIZE];
int requestLength;
char* path = new char[REQUEST_MAX_SIZE];

buffer.clear();

currentWorkingPath = getcwd(path,REQUEST_MAX_SIZE);

if ( (requestLength = read(communication->getReadStream(), request, REQUEST_MAX_SIZE) )< 0)
    perror("Server-side read error - receiveRequestFromClient()!\n");

request[requestLength] = 0;

pipeSlave = communication;

interpretRequest(string(request));

delete path;
}


void Server::interpretRequest(string request) {

string fileName;
string myFindRequest("myfind ");
string myStatRequest("mystat ");
string cdRequest("cd");
int pid;

if (request.compare( string("quit") ) == 0)
    exit(0);

if ( request.find(myFindRequest) != std::string::npos )
    {
     fileName = request.substr( myFindRequest.length() );
     runMyFind(fileName);
     return;
    }

if ( request.find(myStatRequest) != std::string::npos )
    {
     fileName = request.substr( myStatRequest.length() );
     runMyStat(string(currentWorkingPath),fileName);
     return;
    }

switch (pid = fork() ) {

    case -1 :
    perror("Server-side fork error!");
    exit(1);
    case 0 : // child
    runGenericCommand(request);
    default : //parent
    wait(NULL);
    buffer = string("  ");
    }

}

bool Server::isCdCommand(string command) {

return command.find(string("cd")) != std::string::npos;
}

string Server::sendResponseToClient() {

string result;

if (buffer.compare(string("  ")) != 0)
    result = string("[") + to_string(buffer.length()) + string("] ") + string(buffer);
    else
    result = buffer;

char* stringForPipe = new char[result.size() +1];
copy(result.begin(), result.end(), stringForPipe);
stringForPipe[result.size()] = 0;

if (  write(pipeSlave->getWriteStream(),stringForPipe,strlen(stringForPipe) ) == -1 )
    perror("Client-side error - getRequestFromConsole()!\n");

return result;
}

void Server::runGenericCommand(string command){

char * charCommand = new char[command.size() + 1];

copy(command.begin(), command.end(), charCommand);
charCommand[command.size()] = '\0';


prepareCommandList(charCommand);


if (execvp(commandList[0],commandList) <0 )
    {
     perror("Execvp error!");
     exit(1);
    }

}

void Server::prepareCommandList(char* command)
{
char *p;
int index = 0;

p = strtok(command," ");

do {
    commandList[index] = p;
    index = index + 1;
}
while ( (p = strtok(NULL," ")) );

commandList[index] = 0;
}

void Server::runMyStat(string path, string fileName){

struct stat result;
char* charFileName = new char[REQUEST_MAX_SIZE];
char* currentPath = new char[RESPONSE_MAX_SIZE];
copy(path.begin(), path.end(), currentPath);
currentPath[path.size()] = 0;

copy(fileName.begin(), fileName.end(), charFileName);
charFileName[fileName.size()] = 0;

strcat(currentPath,"/");
strcat(currentPath,charFileName);

if ( stat(currentPath,&result) == -1 )
    perror("Server-side error - runMyStat()!\n");
    else
    {
    buffer.append("\n----------------------------------------------------\n");
    buffer.append(string(currentPath));
    buffer.append("\nInode: "); buffer.append( to_string(result.st_ino) ); buffer.append("\n");
    buffer.append("Size: "); buffer.append( to_string(result.st_size) ); buffer.append(" bytes\n");
    buffer.append("Access rights: "); buffer.append( to_string(result.st_mode) ); buffer.append("\n");
    buffer.append("Time of last modification: "); buffer.append( string(ctime(&result.st_mtime)) ) ; buffer.append("\n");

    }

delete[] charFileName;
delete[] currentPath;
}

void Server::runMyFind(string path){

char* charPath = new char[RESPONSE_MAX_SIZE];
char* fileName = new char[path.length() + 1];
copy(path.begin(), path.end(), fileName);
fileName[path.size()] = 0;

charPath = getcwd(charPath,RESPONSE_MAX_SIZE);

findFile(charPath,fileName);

delete fileName;
}

void Server::findFile(char directory[RESPONSE_MAX_SIZE], char pattern[REQUEST_MAX_SIZE]) {

DIR* dir;
struct dirent* directoryEntry;
char newPath[RESPONSE_MAX_SIZE];

dir = opendir(directory);

if (!dir)
    exit(1);

while ( (directoryEntry = readdir(dir)) != NULL) {

    if ( isDotsDirectory(directoryEntry -> d_name) )
        continue;

    strcpy(newPath, directory);
    strcat(newPath, "/");
    strcat(newPath, directoryEntry -> d_name);

    if ( directoryEntry->d_type == DT_DIR )
          findFile(newPath,pattern);

    if ( isExpectedFile(directoryEntry->d_name, pattern) )
        runMyStat( string(directory), string(directoryEntry->d_name) );

  }

closedir(dir);

}

bool Server::isDotsDirectory(char entryName[REQUEST_MAX_SIZE]) {

    return strcmp(entryName, ".") == 0 || strcmp(entryName, "..") == 0;
}


bool Server::isExpectedFile(char entryName[REQUEST_MAX_SIZE], char pattern[REQUEST_MAX_SIZE]) {

    //return strcmp( entryName, pattern) == 0;
    return strstr(entryName,pattern) != NULL;
}

void Server::runChangeDirectory(string path) {

char * charPath = new char[path.length() + 1];

copy(path.begin(), path.end(), charPath);
charPath[path.size()] = 0;

chdir(charPath);
currentWorkingPath = getcwd(currentWorkingPath,RESPONSE_MAX_SIZE);

delete[] charPath;

}
