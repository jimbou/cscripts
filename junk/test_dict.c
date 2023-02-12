/* A key/value dict system in C */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.c"


int main(int argc, char **argv) {
    /* Create a dict */
    dict_t**dict = dictAlloc();



    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("opcodes.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        char *p = NULL;
        char *p1 =NULL;
        p = strtok(line," ");
        p1=p; //periexei to kleidi diladi to opcode
        p = strtok(NULL,"\n");   //periexei tin energeia
        //printf("%s ",p1);  
        //printf("%s ",p); 
        //printf("%s %s",p,(p++));
         //printf("%s %s ",p ,p++);
        addItem(dict, p1, p); //prosthetoume sto leksiko to zeugos energeia opcode
        printf("You entered %s  with key %s \n", (char *)getItem(*dict, p1), p1);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    /*
    //lets add foo, and bar to the dict 
    addItem(dict, "foo", "10");
    addItem(dict, "bar", "11");
    
    //and print their values 
    printf("%s %s\n", (char *)getItem(*dict, "foo"), (char *)getItem(*dict, "bar"));
    
    char *value ;   // o xaraktiras aston opoio tha diabasoume tin timi tis  energias
    int true_value;  // o int me tin energeia
    value = (char *)getItem(*dict, "foo"); //diabazoume apo leksiko
    sscanf(value, "%d", &true_value); // metatrepoume ton charactira se int
    printf("You   entered: %d \n", true_value);
 
    //lets delete them 
    delItem(dict, "foo");
    delItem(dict, "bar");
    
    //see, their gone, there NULL 
    printf("%s %s\n", (char *)getItem(*dict, "foo"), (char *)getItem(*dict, "bar"));
    
    //add them again to proof it works 
    addItem(dict, "foo", "bar");
    addItem(dict, "bar", "foo");
    addItem(dict, "bar", "pan");
    
    //see, here 
    printf("%s %s\n", (char *)getItem(*dict, "foo"), (char *)getItem(*dict, "bar"));
    
    delItem(dict, "foo");
    delItem(dict, "bar");
    
    dictDealloc(dict);
    */
    
    return 0;
}

