#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

int main(){
    int *loop;
    loop = malloc(sizeof(int));
    assert(loop != NULL);
    *loop = 1;

    FILE *fp;

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        printf("Hello\n");
        fp = fopen("cheat.txt", "w");

        if(fp == NULL) {
            fprintf(stderr,"fopen failed\n");
        }else {
            
            fputc(65, fp);
            
            if(fclose(fp) == EOF)
            {
                fprintf(stderr,"close failed\n");
            }
        }
    } else
    {
        fp = fopen("cheat.txt", "w");
        if(fp==NULL) {
            fprintf(stderr,"fopen failed\n");
        }
        if(fclose(fp) == EOF)
        {
            fprintf(stderr,"close failed\n");
        }

        int temp;

        while(*loop == 1)
        {
            fp = fopen("cheat.txt", "r");
            if(fp == NULL) {
                fprintf(stderr,"Datei konnte nicht geoeffnet werden.\n");
            }else {
                // komplette Datei zeichenweise ausgeben
                while((temp = fgetc(fp))!=EOF)
                {
                    if(temp == 65)
                    {
                        *loop = 0;
                    }
                }
                
                if(fclose(fp) == EOF)
                {
                    fprintf(stderr,"close failed\n");
                }
            }
        }
        printf("Goodby\n");
    }

    if(remove("./cheat.txt") < 0)
    {
        fprintf(stderr,"Remove failed");
    }
    free(loop);
    return 0;
}