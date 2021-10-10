#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(){
    FILE *fp;

    fp = fopen("cheat.txt", "w");

    if(fp == NULL) {
        printf("Datei konnte nicht geoeffnet werden.\n");
    }else {
        fputc(1, fp);
        
        fclose(fp);
    }

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        fp = fopen("cheat.txt", "w");

        if(fp == NULL) {
            printf("Datei konnte nicht geoeffnet werden.\n");
        }else {
            fputc(0, fp);
            
            fclose(fp);
        }
        printf("Hello\n");
    } else
    {
        bool *loop;
        *loop = 1;
        while(*loop == 1)
        {
            fp = fopen("cheat.txt", "r");

            if(fp == NULL) {
                printf("Datei konnte nicht geoeffnet werden.\n");
            }else {
                // komplette Datei zeichenweise ausgeben
                *loop = (fgetc(fp) == '1');
                fclose(fp);
            }
        }
        printf("Goodby\n");
    }
}