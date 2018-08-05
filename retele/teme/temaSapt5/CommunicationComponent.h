#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class CommunicationComponent {

    private:
    int descriptors[2];
    string type;

    void setToPipe();
    void setToFifo();
    void setToSocket();

    public:
    CommunicationComponent(string type);
    int getWriteStream() {return descriptors[1];};
    int getReadStream() {return descriptors[0];};
    void closeWriteStream() { close(descriptors[1]); };
    void closeReadStream() { close(descriptors[0]); };
};
