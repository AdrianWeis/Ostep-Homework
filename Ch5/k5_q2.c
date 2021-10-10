#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {
    close(STDOUT_FILENO);
    open("./k5_q2.output", O_CREAT|O_WRONLY|O_TRUNC);
    printf("Hello");
}