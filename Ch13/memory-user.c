#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
    if (argc != 2){
        printf("Fehlerhafteraufruf: memory-user byteAnzahl\n");
        return -1;
    }

    int bAnz;
    char *p;

    errno = 0;
    long conv = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        fprintf(stderr,"Second Argument needs to be a Int\n");
        return -1;
    } else {
        bAnz = conv/sizeOf(int);
    }

    int *array;
    array = (int) calloc(sizeOf(int)*bAnz);
    assert(array);
    
    printf("Realisierte Arraysize: %d\n", sizeof(array));
    printf("Programm ID von memory-user:%d\n", getPid());

    for (int s = 0; s <= 10000; s++)
    {
        for (int i = 0; i <= bAnz; i++)
        {
            array[i];
        }
    }
}