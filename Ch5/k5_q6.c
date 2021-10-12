#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int wstatus;
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        //int rc_wait = wait(NULL);
        //printf("Return of wait:%d",rc_wait);
        printf("Hello\n");
    } else
    {
        int rc_wait = waitpid(rc,&wstatus,0);
        if(rc_wait < 0)
        {
            fprintf(stderr,"Wait failed\n");
        }
        printf(" and Goodby\n");
        printf("Return of wait:%d\n",rc_wait);
    }
    return(0);
}