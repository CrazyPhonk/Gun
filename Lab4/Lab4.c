#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
int main (int argc, char * argv [])
{
    int fd[2];
    pipe(fd);
    char buf[256];
    pid_t pid[argc];
    pid_t pidToWait;
    char str[] = "Simple string\n";
    for (int i = 1; i< argc+1; i+=2){
       // sleep(1);
        pid[i] = fork();
        if(pid[i] == 0){
            close(fd[0]);
            write(fd[1], str, (strlen(str)+1));
            pidToWait = getpid();
            int b = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", argv[1], argv[i+1], argv[i+2], NULL);
            if(b<0){
                printf("Execlp error\n");
                exit(-1);
            }
            waitpid(pid[i], 0,0);
            return 1;
        }
        else if(pid[i] > 0){
            printf("a\n");
            close(fd[1]);
            read(fd[0], buf, sizeof(buf));
            printf("%s\n", buf);
            close(fd[1]);
            int a = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", argv[1], argv[i+3], argv[i+4], NULL);\
            if(a<0){
                printf("Execlp error2\n");
                exit(-1);
            }
                        //sleep(1);
                        return 0;
        }
        else{
            printf("Fork error\n");
            exit(-2);
        }
        
    }
}