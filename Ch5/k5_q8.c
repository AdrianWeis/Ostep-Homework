#define _GNU_SOURCE
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int filedes[2], err1;//, err2;
    char buffer[22];

    if (pipe(filedes) < 0)
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }

    int rc1 = fork();
    if(rc1 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (rc1 == 0)
    {
        if(close(filedes[0]) < 0)
        {
            fprintf(stderr,"Close Failed\n");
        }
        if(dup2(filedes[1],1)< 0)
        {
            fprintf(stderr,"dup2 failed\n");
        }
        /*char temp[2];
        temp[0] = 'H';
        temp[1] = 'i';
        temp[2] = '\n';*/
        printf("test\n");
        /*err2 = write(filedes[1],temp,12);
        if(err2 == -1) {
            fprintf(stderr, "Write Failed\n");
            exit(1);
        }*/
    } 
    else
    {
        if(wait(NULL) < 0)
        {
            fprintf(stderr,"Wait failed\n");
        }

        int rc2 = fork();
        if(rc2 < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } 
        else if (rc2 == 0)
        {
            if(close(filedes[1]) < 0)
            {
                fprintf(stderr,"Close Failed\n");
            }
            printf("Sollte vor test stehen\n");
            if(dup2(filedes[0],0) < 0)
            {
                fprintf(stderr,"dup2 failed\n");
            }
            err1 = read(STDIN_FILENO,buffer,22);
            if (err1 == -1)
            {
                printf("reading error");
                exit(-1);
            }
            printf("%s\n",buffer);
        } 
        else
        {
            
        }
       
    }
    return(0);
}