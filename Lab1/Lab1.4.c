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
if (argc != 3)
    {
    printf("Usage: %s old-file new-file \n", argv[0]); exit(-1);
    }
/* Открытие файлов ввода и вывода */
inputFd = open (argv[1], O_RDONLY);
if (inputFd == -1)
    {
    printf ("Error opening file %s\n", argv[1]) ; exit(-2);
    }
openFlags = O_CREAT | O_WRONLY | O_TRUNC;
filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw - rw - rw - */
outputFd = open (argv [2], openFlags, filePerms);
if (outputFd == -1)
    {
    printf ("Error opening file %s\n ", argv[2]) ; exit(-3);
    }
/* Перемещение данных до достижения конца файла ввода или возникновения ошибки */
while (numRead > 0)
    {
        if (buf == "\r" | buf == "\n")
        write(outputFd, argv[3], 1);
        numRead=read(outputFd, buf, sizeof(char));
        write(outputFd, buf, sizeof(char));
    }
}