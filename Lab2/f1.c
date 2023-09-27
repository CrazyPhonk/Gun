#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
void f1(int inputFd, int outputFd, char symb){
    char buf[1];
int numRead=read(inputFd, buf, 1);
while (numRead > 0)
    {
        if (buf[0] == '\r' || buf[0]== '\n') {
            write(outputFd, symb, 1);
            printf("%c\n", symb);
            }
        write(outputFd, buf[0], 1);
        numRead=read(inputFd, buf[0], 1);
}
}