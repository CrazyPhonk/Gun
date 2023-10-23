#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
    int fd[2], fd2[2];
    pipe(fd);
    pipe(fd2);
    close (fd[0]);
    for(int i = 1; i<=argc; i++)
    write(fd[1], argv[i], strlen((argv[i])+1));
    return 0;
}