#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
  int *x =(int*) malloc(sizeof(int));
  printf("x: %d\n", *x);
  return 0;
}
