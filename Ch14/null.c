#include <stdio.h>
#include <assert.h>

int main()
{
    int* p;
    p = malloc(sizeof(int));
    assert(p != NULL);
    *p = NULL;
    printf("Dereferenzierungstest ergibt:%d",*p);
    free(p);
    return 0;
}