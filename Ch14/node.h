#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct daten
{
    int *daten;
    int laenge;
};

void add(struct daten *pointer, int data);
void printDaten(struct daten *pointer);

#endif