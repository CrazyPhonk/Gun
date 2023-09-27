#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#define BUF_SIZE 1024


int main(int argc, char * argv[])
{
    char buf[BUF_SIZE];
    ssize_t numRead;
    FILE * in  = fopen(argv[1],"r");
    FILE * out = fopen(argv[2],"rw");
    if (&in < 0)
    {
        printf("Error open file1\n");
        return 1;
    }
    if (&out < 0)
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
    }
    
    //fclose(in);
    //fclose(out);
}