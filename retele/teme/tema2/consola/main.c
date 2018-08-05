#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define DMAX 256
#define CMAX 16


char* commandList[CMAX];
char* command;

void prepareCommandList();

int main()
{

    pid_t pid;
    int status=0;
    int nbytes = DMAX;

    while (1)
    {
        printf("Entery your command: ");
        getline(&command,&nbytes,stdin);

        if ( strcmp(command,"exit\n") == 0 )
            exit(0);

        prepareCommandList();

        pid = fork();

        switch(pid)
        {
        case -1:
            perror("Fork error!");
            exit(1);

        case 0: //child process
            printf(commandList[0]);
            if (execvp(commandList[0],commandList) <0 )
            {
                perror("Execvp error!");
                exit(1);
            }
            exit(0);

        default: //parent process
            wait(status);
        }
    }

    return 0;
}

void prepareCommandList()
{
char *p;
int index = 0;

p = strtok(command," ");

do {
    commandList[index] = p;
    index = index + 1;
}
while ( p = strtok(NULL," ") );

commandList[index] = 0;
}
