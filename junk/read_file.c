#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("opcodes.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        char *p = NULL;
        char *p1 =NULL;
        p = strtok(line," ");
        p1=p;
        p = strtok(NULL," ");
        printf("%s ",p1); 
        printf("%s ",p); 
        //printf("%s %s",p,(p++));
         //printf("%s %s ",p ,p++);

    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}