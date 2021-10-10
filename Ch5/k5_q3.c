#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(){
    FILE *fp;

    remove("cheat.txt");

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
            fputc(1, fp);
            
            fclose(fp);
        }
        printf("Hello\n");
    } else
    {
        fp = fopen("cheat.txt", "w");
        fclose(fp);

        bool loop = 1;
        int temp;

        while(loop != 0)
        {
            fp = fopen("cheat.txt", "r");

            if(fp == NULL) {
                printf("Datei konnte nicht geoeffnet werden.\n");
            }else {
                // komplette Datei zeichenweise ausgeben
                while((temp = fgetc(fp))!=EOF)
                {
                    if(temp == 1)
                    {
                        loop = 0;
                    }
                }
                fclose(fp);
            }
        }
        printf("Goodby\n");
    }
}