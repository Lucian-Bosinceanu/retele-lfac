#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define INF 2000000000
#define MSG1 "Comunicam prin socketi!"
#define MSG2 "Atentie!Socketpair() o generalizarea a pipe-urilor"

using namespace std;

struct expression {

    int operator1;
    int operator2;
    char operation;
};
expression exp;

void initSocket();
int evaluateExpression(expression _exp);

int sockp[2], child;
char msg[1024];

int main()
  {

    int result;

    while (1) {

        result = -INF;
        cout<<"Insert expression: ";
        cin>>exp.operator1 >> exp.operation >> exp.operator2;
        if (cin.eof()) break;

        initSocket();
        if ((child = fork()) == -1) perror("Err...fork");
        else
          if (child)   //parinte
            {
                close(sockp[0]);

                write(sockp[1],&exp,sizeof(exp));

                wait(NULL);
                read(sockp[1],&result,sizeof(result));
                close(sockp[1]);
              }
            else     //copil
              {
                close(sockp[1]);
                read(sockp[0],&exp,sizeof(exp));

                result = evaluateExpression(exp);

                write(sockp[0],&result,sizeof(result));
                close(sockp[0]);
                exit(0);
               }
        cout<<"Result is: "<<result<<'\n';

    }


}

int evaluateExpression(expression _exp) {

switch(exp.operation) {
        case '+': return exp.operator1 + exp.operator2;
        case '-': return exp.operator1 - exp.operator2;
        case '*': return exp.operator1 * exp.operator2;
        case '/': if ( exp.operator2 ) return exp.operator1 / exp.operator2;
        }

return -INF;
}

void initSocket()
{

if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockp) < 0)
      {
        perror("Err... socketpair");
        exit(1);
      }
}


