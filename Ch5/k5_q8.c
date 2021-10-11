#define _GNU_SOURCE
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    int filedes[2];
    char buffer[256];
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
        int rc2 = fork();
        if(rc2 < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        } 
        else if (rc2 == 0)
        {
            close(filedes[1]);
            dup2(0,filedes[0]);
            read(filedes[0],buffer,12);
            printf("Sollte vor test stehen");
            printf("%s\n",buffer);
        } 
        else
        {
            
        }
       
    }
    return(0);
}