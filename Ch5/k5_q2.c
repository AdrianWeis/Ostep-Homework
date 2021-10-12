#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    close(STDOUT_FILENO);
    open("./k5_q2.txt", O_CREAT|O_WRONLY|O_TRUNC);
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        for (int i; i < 100; i++)
        {
            printf("AaAa");
        }
    } else
    {
        for (int n; n < 100; n++)
        {
            printf("BbBb");
        }
        wait(NULL);
    }
    return(0);
}