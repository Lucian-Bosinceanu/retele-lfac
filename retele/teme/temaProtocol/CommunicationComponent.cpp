#include "CommunicationComponent.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

using namespace std;

CommunicationComponent::CommunicationComponent(string type){

string fifoS("fifo");
string pipeS("pipe");
string socketS("socket");

if (type.compare(fifoS) == 0)
    {
    setToFifo();
    this->type = fifoS;
    return;
    }

if (type.compare(pipeS) == 0)
    {
    setToPipe();
    this->type = pipeS;
    return;
    }

if (type.compare(socketS) == 0)
    {
    setToSocket();
    this->type = socketS;
    return;
    }

fprintf(stderr, "Could not set communication component!\n");
exit(1);

}

void CommunicationComponent::setToPipe() {

if (pipe (descriptors) == -1)
    {
      fprintf (stderr, "Could not create pipe!\n");
      exit (1);
    }

}

void CommunicationComponent::setToFifo() {

int flags;

mknod(FIFO_NAME, S_IFIFO | 0666, 0);

descriptors[0] = open("myfifo",O_RDONLY | O_NONBLOCK);
descriptors[1] = open("myfifo",O_WRONLY);

flags = fcntl(descriptors[0],F_GETFL);
flags = flags ^ O_NONBLOCK;

fcntl(descriptors[0], F_SETFL, flags);

}

void CommunicationComponent::setToSocket(){

 if (socketpair(AF_UNIX, SOCK_STREAM, 0, descriptors) < 0)
      {
        perror("Could not create socket!\n");
        exit(1);
      }


}


