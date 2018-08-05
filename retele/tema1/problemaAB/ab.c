#include <fcntl.h>
#include <unistd.h>

int fileDesc;
char* fileName = "ab.txt";

void writeInFile();

int main() {

fileDesc = open(fileName,O_WRONLY);
writeInFile();
close(fileDesc);

return 0;
}

void writeInFile(){

write(fileDesc,"CB",2);
lseek(fileDesc,0,SEEK_SET);
write(fileDesc,"A",1);
}
