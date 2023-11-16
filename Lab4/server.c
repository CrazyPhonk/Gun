#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    char buf[256]; 
    char buf2[256];
    char *istr;
    close(fd[1]);
    read(fd[0], buf, sizeof(buf));
    istr = strtok(buf, " ");
    return 0;
}