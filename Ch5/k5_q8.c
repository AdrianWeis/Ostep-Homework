#define _GNU_SOURCE
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    int filedes[2];
    char buffer[256];
    char *string[256];

    int rc1 = fork();
    if(rc1 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (rc1 == 0)
    {
        dub2(1,filedes[1]);
        printf("Hi");
        pipe2(filedes[1],0);
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
            dup2(0,filedes[0]);
            pipe2(filedes[0],0);
            read(0,buffer,64);
            strcpy(string,buffer);
            printf(string);
        } 
        else
        {
            
        }
       
    }
    return(0);
}