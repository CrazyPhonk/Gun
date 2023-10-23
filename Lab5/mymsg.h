#ifndef __MYMSG_H__
#define __MYMSG_H__

#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>


#define MSGPERM 0600
#define MSGTXTLEN 128
#define MSGKEY 32769

struct msg_buf{
    long mtype;
    char mtext[MSGTXTLEN];
    int len;
} msg;
#endif