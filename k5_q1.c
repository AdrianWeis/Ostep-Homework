#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
    int *x;
    x = malloc(sizeof(int));
    assert(x != NULL);
    *x = 100;

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        printf("Current Value of x=%d\n", x);
        *x = *x - 1;
        printf("Value Change to:%d\n",x);
    } else
    {
        printf("Current Value of x=%d\n", x);
        *x = 42;
        printf("Value Change to:%d\n",x);
    }
    return 0;
}