#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
// пример программы обработки текстового файла средствами системых вызовов Linux
// учебник "Системное программирование в среде Linux", Гунько А.В.
int main(int argc, char *argv[]) {
int handle, numRead, total= 0;
char buf;
if (argc<2) {
    printf("Usage: file textfile\n");
    exit(-1);
    }
// низкоуровневое открытие файла на чтение
handle = open( argv[1], O_RDONLY);
if (handle<0) {
    printf("Error %d (%s) while open file: %s!\n",errno, strerror(errno),argv[1]);
    exit(-2);
    }
// цикл до конца файла
do {
// посимвольное чтение из файла
numRead = read( handle, &buf, 1);
if (buf == 0x20) total++; } 
while (numRead > 0);
// Закрытие файла
close( handle); 
printf("(PID: %d), File %s, spaces = %d\n", getpid(), argv[1], total);
// возвращаемое программой значение
return( total); }