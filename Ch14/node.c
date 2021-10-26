#include "node.h"

/*int getSize(Node &pointer)
{
    int size = 0;
    Node* temp;
    if (pointer.prev == NULL && pointer.next == NULL)
    {
        return 0;
    }
    else if (pointer.prev != NULL)
    {
        temp = pointer.prev;
        while (temp.prev != NULL)
        {
            temp = temp.prev;
        }
    }
    else
    {
        temp = pointer.next;
        size++;
    }

    while (temp.next != NULL)
    {
        size++;
    }
    return size;
}*/

void add(struct daten* pointer, int data)
{
    void* test;
    if(pointer->laenge == 0)
    {
        pointer->daten = realloc(pointer->daten,sizeof(int));
        pointer->laenge++;
        return;
    }
    pointer->daten = realloc(pointer->daten,sizeof(int));
    assert(test != NULL);
    pointer->daten[pointer->laenge] = data;
    pointer->laenge++;

    return;
}

void printDaten(struct daten *pointer)
{
    printf("Anzahl der Daten = %d", pointer->laenge);
}

int main()
{
    struct daten v1;
    add(&v1,1);
    struct daten v2;
    add(&v2,2);
    add(&v2,3);
    struct daten array[] = {v1,v2};

    printDaten(&array[0]);
    printDaten(&array[1]);
}