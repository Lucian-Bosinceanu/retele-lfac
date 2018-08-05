#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define COUNT 5


int main()
{

    pid_t pid;
    int status=0;
    int procCount = 0;
    int i;

    for (i = 1; i <= COUNT ; i++)
    {
        procCount++;

        pid = fork();

        switch(pid)
        {
        case -1:
            perror("Fork error!");
            exit(1);

        case 0: //child process
            printf("Sunt procesul numarul ");
            printf("%d",procCount);
            printf("\n");
            exit(0);

        default: //parent process
            wait(status);
        }
    }

    return 0;
}
