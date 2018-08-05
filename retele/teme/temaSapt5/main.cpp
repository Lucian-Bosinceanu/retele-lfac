#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Client.h"
#include <string>

using namespace std;


int main(int argc, char* argv[])
{

    string connectionType(argv[1]);
    Client* client = new Client();

    client->run(connectionType);

    return 0;
}

