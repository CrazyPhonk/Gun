#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
int main (int argc, char * argv [ ])
{
    pid_t pid[(argc-2)/2];
    int stat, status=-1;
    //pid_t id;
    //pid_t pidToWait;
    for (int i = 0; i< (argc-2)/2; i++){
        //sleep(1);
        printf("%d\n", argc);
        pid[i] = fork();
        if(pid[i] == 0){
            printf("Child PID: %d\n", pid[i]);
            printf("%s %s %s\n", argv[1], argv[i*2+2], argv[i*2+3]);
            int b = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", argv[1], argv[i*2+2], argv[i*2+3], NULL);
            if(b<0){
                printf("Execlp error\n");
                exit(-1);
            }           
            return 0;
        }
        else if(pid[i] > 0){
            printf("Parent PID: %d\n", pid[i]);
            sleep(1);
            status = waitpid(pid[i], &stat, 0);
            if (pid[i]=status)
            printf("Result = %d\n", WEXITSTATUS(stat));
        }
        else{
            printf("Fork error\n");
            exit(-2);
        }
    }
}