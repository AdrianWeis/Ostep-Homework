#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        close(STDOUT_FILENO);
        printf("Hello\n");
    } else
    {
       
    }
    return(0);
}