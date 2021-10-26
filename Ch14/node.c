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

daten* add(daten* pointer, int data)
{
    daten *temp;
    if(pointer->laenge == 0)
    {
        pointer->daten[0] = data;
        return pointer;
    }
    temp.daten = realloc(pointer->daten,sizeof(int));
    assert(temp.daten != NULL);
    temp.laenge = pointer->laenge;
    temp.daten[pointer->laenge] = data;
    temp.laenge++;

    return temp;
}

void printDaten(daten* pointer)
{
    printf("Anzahl der Daten = %d", pointer->laenge);
}

int main()
{
    daten *v1;
    v1 = add(v1,1);
    daten *v2;
    v2 = add(v2,2);
    v2 = add(v2,3);
    daten *array[] = {v1,v2};

    printDaten(array[0]);
    printDaten(array[1]);
}