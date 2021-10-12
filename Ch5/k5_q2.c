#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    int fd = open("./k5_q2.txt", O_CREAT|O_WRONLY|O_TRUNC);
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        dup2(fd,STDOUT_FILENO);
        for (int i; i < 100; i++)
        {
            printf("AaAa");
        }
    } else
    {
        dup2(fd,STDOUT_FILENO);
        for (int n; n < 100; n++)
        {
            printf("BbBb");
        }
    }
    return(0);
}