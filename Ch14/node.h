#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct Daten
{
    int daten[1];
    int laenge;
};

typedef struct Daten daten;

void add(daten *pointer, int data);
void printDaten(daten *pointer)

#endif