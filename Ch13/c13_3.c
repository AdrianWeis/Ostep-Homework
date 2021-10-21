#define BIGNUM = 1000;
#include <assert.h>
#include <stdlib.h>

int main()
{
    double *array;
    array = (double) calloc(sizeOf(double)*BIGNUM);
    assert(array);

    for (int i = 0; i <= BIGNUM; i++)
    {
        for (int i = 0; i <= BIGNUM; i++)
        {
            array[i];
        }
    }
}