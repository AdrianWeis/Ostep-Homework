#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
    int* p;
    p = malloc(sizeof(int)* 100);
    assert(p != NULL);
    for(int i= 0; i < 100; i++)
    {
        p[i]=i;
    }
    //p[100] = 0;

    //free(p);
    //printf("Test nach free an index 75:%d\n", p[75]);

    free(&p[1]);

    printf("Dereferenzierungstest ergibt:%d\n",*p);
    printf("Größe des Pointers:%ld\n",sizeof(p));
    printf("Größe von Integern:%ld\n",sizeof(int));
    printf("Größe des dereferenzierten Pointers:%ld\n",sizeof(*p));

    free(p);
    return 0;
}