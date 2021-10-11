#define _GNU_SOURCE
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int filedes[2], err1;
    char buffer[22];

    if (pipe (filedes) < 0)
    {
      perror ("pipe");
      exit (EXIT_FAILURE);
    }

    int rc1 = fork();
    if(rc1 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (rc1 == 0)
    {
        close(filedes[0]);
        dup2(1,filedes[1]);
        char temp[2];
        temp[0] = 'H';
        temp[1] = 'i';
        temp[2] = '\n';
        printf("test\n");
        write(filedes[1],temp,12);
    } 
    else
    {
        wait(NULL);

        int rc2 = fork();
        if(rc2 < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } 
        else if (rc2 == 0)
        {
            close(filedes[1]);
            printf("Sollte vor test stehen");
            dup2(0,filedes[0]);
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