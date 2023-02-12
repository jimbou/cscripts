/* A key/value dict system in C */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dict.c"


char* give_opcode(char *argument, char *line)  //returns the name of the command in our format 
{
  
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        char *p = NULL;
        char *p1 =NULL;
        char *p2 =NULL;
        char *opcode =NULL;
        char *op1 =NULL;
        char *op2 =NULL;
        char *op3 =NULL;
        char *temp =NULL;
        char *temp2 =NULL;
        char Delimit[] = " ,";
        
        p = strstr(line, argument);
        
        p1 = strtok(p," ");   
        p2 =strtok(NULL,"\n"); //periexei tin actuall entoli me kena stin arxi
        while (isspace(*p2)){
            ++p2;}             //katharizoume ta kena stin arxi
        printf("%s \n",  p2); 
        opcode  =strtok(p2,Delimit); //pairnoume to onoma tis entolis
        if (opcode != NULL) {   //pairnoume proto operator
            op1 = strtok(NULL, Delimit); }
        if (op1!= NULL) {       //pairnoume deutero operator
            op2 = strtok(NULL,Delimit); }
        if (op2!= NULL) {       //pairnoume trito operator
            op3= strtok(NULL,Delimit); }

        printf("%s %s %s %s\n",  opcode , op1, op2 ,op3);
        return opcode;
    
}
int main(int argc, char *argv[]) {
    
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("trace.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    if (argc<2 ){                //if an argument is not provided then error message and fail 
        printf("You have not given the name of the file that was executed \n");
        return 1;}
    else{
        strcat(argv[1] ,") ");   //this will be the telling where the gerbage stops and where actuall commands start
       }

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        char *result =NULL;
        result =give_opcode(argv[1],line);
/*
        char *p = NULL;
        char *p1 =NULL;
        char *p2 =NULL;
        char *opcode =NULL;
        char *op1 =NULL;
        char *op2 =NULL;
        char *op3 =NULL;
        char *temp =NULL;
        char *temp2 =NULL;
        char Delimit[] = " ,";
        
        p = strstr(line, argv[1]);
        
        p1 = strtok(p," ");   
        p2 =strtok(NULL,"\n"); //periexei tin actuall entoli me kena stin arxi
        while (isspace(*p2)){
            ++p2;}             //katharizoume ta kena stin arxi
        printf("%s \n",  p2); 
        opcode  =strtok(p2,Delimit); //pairnoume to onoma tis entolis
        if (opcode != NULL) {   //pairnoume proto operator
            op1 = strtok(NULL, Delimit); }
        if (op1!= NULL) {       //pairnoume deutero operator
            op2 = strtok(NULL,Delimit); }
        if (op2!= NULL) {       //pairnoume trito operator
            op3= strtok(NULL,Delimit); }

        printf("%s %s %s %s\n",  opcode , op1, op2 ,op3);
   */
  printf("Result is %s \n",  result);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    
    
    return 0;
}

