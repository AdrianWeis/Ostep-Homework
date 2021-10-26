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
    printf("Größe des Pointers:%ld\n",sizeof(p));
    printf("Größe von Integern:%ld\n",sizeof(int));
    printf("Größe des dereferenzierten Pointers:%ld\n",sizeof(*p));
    free(p);
    return 0;
}