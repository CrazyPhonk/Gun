#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
void f1(int inputFd, int outputFd, char symb){
    char buf[1];
   // printf("%d\n", 45);
int numRead=read(inputFd, buf, 1);
//char* symb2 = &symb;
while (numRead > 0)
    {
        //printf("%d\n", 11);
        if (buf[0] == '\r' || buf[0]== '\n') {
            //printf("%d\n", 232);
            if(write(outputFd, &symb, 1)<0){
                //printf("%c\n", symb);
                printf("Write symbol error\n");
                exit(-4);
            }
            //printf("%d\n", 222);
            }
        if( write(outputFd, buf, 1)<0){
            printf("Buf = %c\n", buf[0]);
            printf("Error\n");
            exit(-5);
        }

        numRead=read(inputFd, buf, 1);
        /*if (numRead <= 0){
            printf("numRead <= 0\n");
        }*/
}
}