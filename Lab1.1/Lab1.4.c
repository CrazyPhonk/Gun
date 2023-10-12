#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#define BUF_SIZE 1024
// пример программы обработки текстового файла средствами системых вызовов Linux
// учебник "Системное программирование в среде Linux", Гунько А.В., стр. 22
int main (int argc, char * argv [ ])
{
int inputFd, outputFd, openFlags;
mode_t filePerms ;
ssize_t numRead;
char buf[1];
char buf2[1];
buf2[0] = argv[1][0];
//printf("%c\n", buf2[0]);
/* Открытие файлов ввода и вывода */
inputFd = open (argv[3], O_RDONLY);
//printf("%d\n", inputFd);
if (inputFd == -1)
    {
    printf ("Error opening file1 %s\n", argv[3]) ; exit(-2);
    }
openFlags = O_CREAT | O_WRONLY | O_TRUNC;
filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw - rw - rw - */
outputFd = open (argv [2], openFlags, filePerms);
if (outputFd == -1)
    {
    printf ("Error opening file2 %s\n ", argv[2]) ; exit(-3);
    }
/* Перемещение данных до достижения конца файла ввода или возникновения ошибки */
numRead=read(inputFd, buf, 1);
while (numRead > 0)
    {
        if (buf[0] == '\r' || buf[0] == '\n') {
            write(outputFd, buf2, 1);
            //printf("%c\n", buf2[0]);
            }
        write(outputFd, buf, 1);
        numRead=read(inputFd, buf, 1);
        
    }
    printf("Complete %s\n", argv[2]);
    return 10;
}