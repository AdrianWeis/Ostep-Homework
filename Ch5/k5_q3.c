#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main(){
    int *loop;
    loop = malloc(sizeof(int));
    assert(loop != NULL);
    *loop = 1;

    FILE *fp;

    if( remove( "./cheat.txt" ) != 0 ){
        perror( "Error deleting file" );
    } else {
        puts( "File successfully deleted" );
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
            fputc(65, fp);
            
            fclose(fp);
        }
        printf("Hello\n");
    } else
    {
        fp = fopen("cheat.txt", "w");
        fclose(fp);

        int temp;

        while(*loop == 1)
        {
            fp = fopen("cheat.txt", "r");

            if(fp == NULL) {
                printf("Datei konnte nicht geoeffnet werden.\n");
            }else {
                // komplette Datei zeichenweise ausgeben
                while((temp = fgetc(fp))!=EOF)
                {
                    if(temp == 65)
                    {
                        *loop = 0;
                    }
                }
                fclose(fp);
            }
        }
        printf("Goodby\n");
    }
    free(loop);
    return 0;
}