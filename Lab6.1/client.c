#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    key_t key = 5678;
    int *shm, *s, shmid;    
    if ((shmid = shmget(key,  size, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    s = shm;
    
    for (int i = 0; i < count; i++){
		printf("%d", *s);
		s++;
	}
    *shm = -1;
    
    if (shmdt(shm) < 0) {
		printf("Ошибка отключения\n");
		exit(1);
	} 
    exit(0);
}
