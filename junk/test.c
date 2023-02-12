/* A key/value dict system in C */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dict.c"

char * registers [] = { "%eax" , "%ebx" ,"%ecx", "%edx", "%cs", "%ds", "%es", "%fs", "%gs", "%ss","%esi", "%edi" , "%ebp", "%eip" ,"%esp", "%ax", "%bx", "%cx" , "%dx" ,"%ah" ,"%al" ,"%bh" ,"%bl" , "%ch" ,"%dh" ,"%dl" ,"%rax", "%rcx" ,"%rdx" ,"%rbx" ,"%rsp" ,"%rbp" ,"%rsi" ,"%rdi" ,"%sp" ,"%bp" ,"%si" ,"%di" ,"%spl" ,"%bpl" ,"%sil" ,"%dil" , "%ss" ,"%cs" ,"%ds" ,"%es" ,"%fs" ,"%gs" ,"%eflags" ,"%eip","%r8", "%r9","%r10", "%r11", "%r12","%r13", "%r14","%r15","%r8d", "%r9d","%r10d", "%r11d", "%r12d","%r13d", "%r14d","%r15d", "%r8w", "%r9w","%r10w", "%r11w", "%r12w","%r13w", "%r14w","%r15w","%r8b", "%r9b","%r10b", "%r11b", "%r12b" ,"%r13b", "%r14b", "%r15b"}; //size =49


bool StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}


bool Isnumber (char *str ){
    for (int i = 0; i < strlen(str); i++) {
        char*temp =str;
        if(!isdigit((str[i]))){return 0;}
        temp++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    
    // char *temp =NULL;
    char *a = "89889893";
    
   if (Isnumber(a)){printf("It is a number %s \n",a);}
    //b=strtok(a,"a");
    /*if (StartsWith(a,"(")){a++;}
       
     if (((strchr(a, ')') != NULL) && (strchr(a, '(') == NULL))){
           char temp[strlen(a)] = " ";  
  temp[strlen(a)-1] = '\0';
        }*/
    
    
    return 0;
}