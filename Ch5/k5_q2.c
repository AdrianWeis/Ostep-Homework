#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {
    close(STDOUT_FILENO);
    open("./k5_q2.txt", O_CREAT|O_WRONLY|O_TRUNC);
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        printf("Hello");
    } else
    {
        printf(" and Goodby");
    }
}