#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
    int* p;
    p = malloc(sizeof(int));
    assert(p != NULL);
    *p = NULL;
    printf("Dereferenzierungstest ergibt:%d\n",*p);
    //free(p);
    return 0;
}