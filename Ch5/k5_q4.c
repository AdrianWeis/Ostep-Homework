#define _GNU_SOURCE 
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>



int main() {

    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        char* myargs[2];
        myargs[0] = strdup("ls");
        myargs[1] = NULL;
        execvp(myargs[0],myargs);
    }
    else
    {
        int rc_wait = wait(NULL);
    }
    return 0;
}