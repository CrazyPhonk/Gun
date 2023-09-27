#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
int main (int argc, char * argv [ ])
{
    if(argc != 4){
        printf("Wrong number of arguments\n");
        exit(-2);
    }
    if (fork() == 0){
        printf("Child process\n");
        int a = execl("/home/egor/VSCode/Gun/Lab1", "Lab1.4", argv[1], argv[2], argv[3][0], NULL);
        printf("a = %d\n", a);
        return 0;
    }
    else if(fork < 0){
        exit(-1);
    }
    else{
        execl("/home/egor/VSCode/Gun/Lab1/Lab1.4", "Lab1.4", argv[1], argv[2], argv[3][0], NULL);
        printf("Parent process\n");
        return 1;
    }
}