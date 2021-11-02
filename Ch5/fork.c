#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

int main()
{
    
    printf("Parent is %d\n", getpid());

    int rc1 = fork();
    printf("%d,%d\n",rc1, getpid());

    int rc2 = fork();
    printf("%d,%d\n",rc2, getpid());

    return 1;
}