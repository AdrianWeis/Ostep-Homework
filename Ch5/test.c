#include <stdio.h>
int main() {
    int a = 12;
    int b = 9;

    int fid = fork();
    if (fid == 0) {
        a++;
    }
    else {
        wait(NULL);
        b = b - 5;
    }
    printf("a = %d, b = %d\t", a, b);
    return 0;
}