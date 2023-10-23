#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

#define MAX_SEND_SIZE 80

char argvSended1 = 0;
            char argvSended2[256] = {0};
            char argvSended3[256] = {0};
            char *a1= &argvSended1, *a2= &argvSended2, *a3=&argvSended3;
            int flag = 0, j = 0, k =0;

struct mymsgbuf {
        long mtype;
        char mtext[MAX_SEND_SIZE];
};

int msgqid, rc;

void send_message(int qid, struct mymsgbuf *qbuf, long type, char *text){
        qbuf->mtype = type;
        strcpy(qbuf->mtext, text);

        if((msgsnd(qid, (struct msgbuf *)qbuf,
                strlen(qbuf->mtext)+1, 0)) ==-1){
                perror("msgsnd");
                exit(1);
        }
}

void read_message(int qid, struct mymsgbuf *qbuf, long type){
        qbuf->mtype = type;
        msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
        printf("Type: %ld Text: %s\n", qbuf->mtype, qbuf->mtext);
        //sprintf();
        argvSended1=qbuf->mtext[0];
            //printf("%s\n", bufRead);
            for(int i = 2; i< 128; i++){
                if (flag == 0 && qbuf->mtext[i] != ' '){
                    argvSended2[j] = qbuf->mtext[i];
                    j++;
                }
                if(qbuf->mtext[i] == ' '){
                    flag = 1;
                }
                //printf("(%c, %d)", bufRead[i], flag);
                if (flag == 1){
                    if (qbuf->mtext[i] != ' '){
                    argvSended3[k] = qbuf->mtext[i];
                    k++;
                }
                }
            }
            //printf("%s\n", argvSended2);
            printf("%c, %s, %s\n", argvSended1, argvSended2, argvSended3);
             char *a1= &argvSended1, *a2= &argvSended2, *a3=&argvSended3;
        int b = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", a1,a2,a3, NULL);
            if(b<0){
                printf("Execlp error\n");
                exit(-1);
            }           
}

int main(int argc, char *argv[]) {
    
    char buf[256] = {0};
    int i, pid[argc], status, stat;
    key_t key;
    int qtype = 1;
    struct mymsgbuf qbuf;
    
    
    //key = ftok(".", 'm');
	if((msgqid = msgget(key, IPC_CREAT|0660)) == -1) {
		perror("msgget");
		exit(1);
	}
        
    for (i = 1; i < 2; i++) {
        pid[i] = fork();
        srand(getpid());

        if (-1 == pid[i]) {
            perror("fork");
            exit(1); 
        } else if (0 == pid[i]) {
            
            char str[128];
            sprintf(str, "%s %s %s", argv[1], argv[2], argv[3]);
            //printf("STR 1 %s --------------\n", str);
            send_message(msgqid, (struct mymsgbuf *)&qbuf,
                                       qtype, str); 
            //printf("STR 2 %s --------------\n", str);
			fflush(stdout);
            exit(0); 
        }
    }
    printf("PARENT\n");
    for (i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("процесс-потомок %d done,  result=%d text=%s\n", i, WEXITSTATUS(stat), argv[i]);
            fflush(stdout); //clear output buffer for printf
        }
    }

		        read_message(msgqid, &qbuf, qtype); 
	//printf("___________________________________________________________%s\n", qbuf->mtext);
	if ((rc = msgctl(msgqid, IPC_RMID, NULL)) < 0) {
		perror( strerror(errno) );
		printf("msgctl (return queue) failed, rc=%d\n", rc);
		return 1;
	}
    return 0;
}