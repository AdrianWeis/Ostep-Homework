#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {

    int fd = open("./k5_q2.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if(fd == -1)
    {
        fprintf(stderr, "Open failed\n");
    }

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        char a[] = "AaAa";
        for (int i; i < 100; i++)
        {
            if(write(fd,a,4) == -1)
            {
                fprintf(stderr,"Write failed\n");
            } 
        }
    } else
    {
        //dup2(fd,STDOUT_FILENO);
        char b[] = "BbBb";
        for (int n; n < 100; n++)
        {
            if(write(fd,b,4) == -1)
            {
                fprintf(stderr,"Write failed\n");
            }
        }
        wait(NULL);
    }
    return(0);
}