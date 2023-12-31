#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int client(key_t key, int n, char massive[][30]);
int server(key_t key, int n);

int main(int argc, char *argv[]){

    key_t key;
    key = 12550;
    pid_t cpid = 0;

    char lenh = 0, g;  
    int lenhsend = 0; // для передачи в функции


    int lenargvs[(argc / 3) + 1];
    lenargvs[0] = 0;
    char mass_of_ukaz[argc / 3][30];   // массив указателей на начало новых 3х входных параметров
    for (g = 0; g < argc / 3; g++) // 
    {
        for (int i = 1; i < 4; i++)  // копирование входных переменных в строку.
        {
            strncpy(&mass_of_ukaz[g][lenh], argv[i + (g * 3)], strlen(argv[i + (g * 3)]));
            strncpy(&mass_of_ukaz[g][strlen(argv[i + (g * 3)]) + lenh], " ", 1);
            lenh = strlen(argv[i + (g * 3)]) + lenh + 1;
            lenhsend = lenhsend + lenh;
        }
        lenh = 0;
    }
    cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(-1);
    }
    else if (cpid == 0) {
        printf("server pid is %d\n", getpid());
        server(key, argc / 3);
        printf("...Done...\n");
    }
    else {
        client(key, argc / 3, mass_of_ukaz);
    }
}
