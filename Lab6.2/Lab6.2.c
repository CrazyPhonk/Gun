#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>
#include <semaphore.h>

#define MAX_LEN 1024


char argvSended1 = 0;
char argvSended2[256] = {0};
char argvSended3[256] = {0};
char *a1= &argvSended1, *a2= &argvSended2, *a3=&argvSended3;
int flag = 0, j = 0, k =0;

union semun {
 int val;                  /* значение для SETVAL */
 struct semid_ds *buf;     /* буферы для  IPC_STAT, IPC_SET */
 unsigned short *array;    /* массивы для GETALL, SETALL */
                           /* часть, особенная для Linux: */
 struct seminfo *__buf;    /* буфер для IPC_INFO */
};

void fileChange(char * str){
    argvSended1 = str[0];
  for(int i = 2; i< 128; i++){
                if (flag == 0 && str[i] != ' '){
                    argvSended2[j] = str[i];
                    j++;
                }
                if(str[i] == ' '){
                    flag = 1;
                }
                //printf("(%c, %d)", bufRead[i], flag);
                if (flag == 1){
                    if (str[i] != ' '){
                    argvSended3[k] = str[i];
                    k++;
                }
                }
            }
            char *a1= &argvSended1, *a2= &argvSended2, *a3=&argvSended3;
        int b = execlp("/home/egor/VSCode/Gun/Lab1.1/Lab1.4", "Lab1.4", a1,a2,a3, NULL);
            if(b<0){
                printf("Execlp error\n");
                exit(-1);
            }           
}	


int main(int argc, char *argv[]){
    sem_t semaphore;
	char str[MAX_LEN];
    sprintf(str, "%s %s %s", argv[1], argv[2], argv[3]);
	int cntStr = 0;
	int i = 1;
	pid_t pid[cntStr];
	int status = 0;
	
	int shmid;
	key_t key = 69;
	char *shm;
	
	//int semid;
    sem_init(&semaphore, 1, 1);
	//union semun arg;
	//struct sembuf lock_res = {0, -1, 0};	//блокировка ресурса
	//struct sembuf rel_res = {0, 1, 0};	//освобождение ресурса
	
	 /* Получим ключ, Один и тот же ключ можно использовать как
    для семафора, так и для разделяемой памяти */
	if ((key = ftok(".", 'S')) < 0) {
		printf("Невозможно получить ключ\n");
		exit(1);
	}
	
	/* Создадим семафор - для синхронизации работы с разделяемой памятью.*/
	//semid = semget(key, 1, 0666 | IPC_CREAT);
	
	/* Установить в семафоре № 0 (Контроллер ресурса) значение "1" */
	//arg.val = 1;
	//semctl(semid, 0, SETVAL, arg);
	 
	 /* Создадим область разделяемой памяти */
	if ((shmid = shmget(key, sizeof(char)*MAX_LEN, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}
    int pidF = fork();
	/* Получим доступ к разделяемой памяти */
	if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("shmat");
		exit(1);
	}
	fflush(stdout);
				
	/* Заблокируем разделяемую память */	
	/*if((semop(semid, &lock_res, 1)) == -1){
		fprintf(stderr, "Lock failed\n");
		exit(1);
	} else{
		printf("Semaphore resources decremented by one (locked) i=%d\n", i);
		fflush(stdout);
	}*/
				
	/* Запишем в разделяемую память сумму */
	strcpy(shm, str);
	sleep(2);
				 
	/* Освободим разделяемую память */
	/*if((semop(semid, &rel_res, 1)) == -1){
		fprintf(stderr, "Unlock failed\n");
		 exit(1);
	} else{
		printf("Semaphore resources incremented by one (unlocked) i=%d\n", i);
		fflush(stdout);
	}*/
				
	printf("String %s\n", shm);
	fflush(stdout);
	 /* Отключимся от разделяемой памяти */
    if (pidF<0){
        i=0;
			perror("fork"); /* произошла ошибка */
				exit(1); /*выход из родительского процесса*/
        }
	if (pidF == 0) {
        sem_wait(&semaphore);
	/* Получим доступ к разделяемой памяти */
    
		if ((shm = (char*)shmat(shmid, NULL, 0)) == (char *) -1) {
            
		perror("shmat");
		exit(1);
	}
    fileChange(shm);
    sem_post(&semaphore);

			fflush(stdout);
		}

	printf("------------------\n");
	fflush(stdout);
	
	/* Удалим созданные объекты IPC */	
	 if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	} else
		printf("Сегмент памяти помечен для удаления\n");
	
	/*if (semctl(semid, 0, IPC_RMID) < 0) {
		printf("Невозможно удалить семафор\n");
		exit(1);
	}*/
    sem_destroy(&semaphore);
	return 0;
}
