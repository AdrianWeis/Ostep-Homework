#include "node.h"
typedef struct Daten Daten;

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

void add(Daten &pointer, int data)
{
    struct Daten temp;
    if(pointer.laenge == 0)
    {
        pointer.data[0] = data;
        return;
    }
    pointer.data = realloc(pointer.data,sizeof(int));
    assert(temp != NULL);
    temp.daten[temp.laenge] = data;
    temp.laenge++;
    return;
}

void printDaten(Daten& pointer)
{
    printf("Anzahl der Daten = %d", pointer.laenge);
}

int main()
{
    Daten *v1;
    add(v1,1);
    Daten *v2;
    add(v2,2);
    add(v2,3);
    Daten *array[] = {v1,v2};

    printDaten(array[0]);
    printDaten(array[1]);
}