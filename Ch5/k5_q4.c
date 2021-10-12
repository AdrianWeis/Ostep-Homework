#define _GNU_SOURCE 
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char*argv[]) {

    if (argc != 2){
        printf("Fehlerhafteraufruf: k5_q4 int\n");
        return -1;
    }

    char *p;

    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        if (strtol(argv[1], &p, 10)==1)
        {
            char* myargs[2];
            myargs[0] = strdup("ls");
            myargs[1] = NULL;
            if(execvp(myargs[0],myargs) < 0)
            {
                fprintf(stderr,"Execute failed\n");
            }
        }
        else if (strtol(argv[1], &p, 10)==2)
        {
            char* myargs[2];
            myargs[0] = strdup("ls");
            myargs[1] = NULL;
            if(execvpe(myargs[0],myargs,environ) < 0)
            {
                fprintf(stderr,"Execvpe failed\n");
            }
        }
        else if (strtol(argv[1], &p, 10)==3)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            if(execv(myargs[0],myargs) < 0)
            {
                fprintf(stderr,"Execute failed\n");
            }
        }
        else if (strtol(argv[1], &p, 10)==4)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            if(execl(myargs[0],"",NULL) < 0)
            {
                fprintf(stderr,"Execute failed\n");
            }
        }
        else if (strtol(argv[1], &p, 10)==5)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            if(execle(myargs[0],"",NULL,NULL) < 0)
            {
                fprintf(stderr,"Execute failed\n");
            }
        }
        else if (strtol(argv[1], &p, 10)==0)
        {
            char* myargs[2];
            myargs[0] = strdup("ls");
            myargs[1] = NULL;
            if(execlp(myargs[0],"",NULL) < 0)
            {
                fprintf(stderr,"Execute failed\n");
            }
        } 
        else
        {
            printf("Options only between 0-5");
        }
        
    }
    else
    {
        int rc_wait = wait(NULL);
        rc_wait = rc_wait + 1;
    }
    return 0;
}