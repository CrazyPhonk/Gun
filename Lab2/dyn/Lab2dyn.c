#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <dlfcn.h>


int main (int argc, char * argv [ ])
{
int inputFd, outputFd, openFlags;
void *library;
int (*f1)(int x, int y, char c);
mode_t filePerms ;
ssize_t numRead;
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

library = dlopen("/home/egor/VSCode/Gun/Lab2/dyn", RTLD_LAZY);
if(!library){
    printf("dll error\n");
    exit(-6);
}
f1 = dlsym(library, "f1.c");
    //printf("%d\n", 12);
(*f1)(inputFd, outputFd, argv[3][0]);
dlclose(library);
}