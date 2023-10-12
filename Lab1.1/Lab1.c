#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_SIZE 1024


int main(int argc, char * argv[])
{
    char buf[BUF_SIZE];
    char buf2[16];
    ssize_t numRead;
    FILE * in  = fopen(argv[1],"r");
    FILE * out = fopen(argv[2],"w");
    if (in == -1)
    {
        printf("Error open file1\n");
        return 1;
    }
    if (out == -1)
    {
        printf("Error open file2\n");
        return 1;
    }
    while (( numRead = read (&in, buf, BUF_SIZE)) > 0)
    {
    if (write (&out, buf, numRead) != numRead)
	{
	printf ("couldn't write whole buffer\n "); exit(-4);
	}
    if (numRead == -1)
	{
	printf ("read error\n "); exit(-5);
	}
    if (close(in) == -1){
        exit(-6);
    }
    if (close(out) == -1)
    exit(-7);
    }
    printf("%s\n", argv[3]);
    printf("%d\n", argc);
}