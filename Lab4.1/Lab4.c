#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
int main (int argc, char * argv [ ])
{
    int fd[2], fd2[2];
    pid_t pid[(argc-2)/2];
    int stat, status=-1;
    pipe(fd);
    pipe(fd2);
    //pid_t id;
    //pid_t pidToWait;
    for (int i = 0; i< (argc-2)/2; i++){
        //sleep(1);
        printf("%d\n", argc);
        pid[i] = fork();
        if(pid[i] == 0){
            
            char bufRead[256]= {0};
            char argvSended1 = 0;
            char argvSended2[256] = {0};
            char argvSended3[256] = {0};
            char *a1= &argvSended1, *a2= &argvSended2, *a3=&argvSended3;
            int flag = 0, j = 0, k =0;
            printf("Child PID: %d\n", pid[i]);
            close(fd[1]);
            close(fd2[0]);
            printf("Read %d\n", read(fd[0], bufRead, sizeof((bufRead))));
            //printf("%s\n",bufRead[0]);
            argvSended1=bufRead[0];
            //printf("%s\n", bufRead);
            for(int i = 2; i< 128; i++){
                if (flag == 0 && bufRead[i] != ' '){
                    argvSended2[j] = bufRead[i];
                    j++;
                }
                if(bufRead[i] == ' '){
                    flag = 1;
                }
                //printf("(%c, %d)", bufRead[i], flag);
                if (flag == 1){
                    if (bufRead[i] != ' '){
                    argvSended3[k] = bufRead[i];
                    k++;
                }
                }
            }
            //printf("%s\n", argvSended2);
            printf("%c, %s, %s\n", argvSended1, argvSended2, argvSended3);
            int b = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", a1,a2,a3, NULL);
            if(b<0){
                printf("Execlp error\n");
                exit(-1);
            }           
            return 0;
        }
        else if(pid[i] > 0){
            char buf[256]= {0};
            printf("Parent PID: %d\n", pid[i]);
            sprintf(buf, "%s %s %s", argv[1], argv[2], argv[3]);
            write(fd[1], buf, (strlen(buf)));
            //sleep(1);
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