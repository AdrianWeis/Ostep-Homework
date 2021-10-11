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
            execvp(myargs[0],myargs);
        }
        else if (strtol(argv[1], &p, 10)==2)
        {
            char* myargs[2];
            myargs[0] = strdup("ls");
            myargs[1] = NULL;
            execvpe(myargs[0],myargs,environ);
        }
        else if (strtol(argv[1], &p, 10)==3)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            execv(myargs[0],myargs);
        }
        else if (strtol(argv[1], &p, 10)==4)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            execl(myargs[0],myargs[1]);
        }
        else if (strtol(argv[1], &p, 10)==5)
        {
            char* myargs[2];
            myargs[0] = strdup("/bin/ls");
            myargs[1] = NULL;
            execle(myargs[0],myargs[1],NULL);
        }
        else if (strtol(argv[1], &p, 10)==0)
        {
            char* myargs[2];
            myargs[0] = strdup("ls");
            myargs[1] = NULL;
            execlp(myargs[0],myargs[1]);
        } 
        else
        {
            printf("Options only between 0-5");
        }
        
    }
    else
    {
        int rc_wait = wait(NULL);
    }
    return 0;
}