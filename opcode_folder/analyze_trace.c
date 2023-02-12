//proto orisma to onoma tou arxeiou pou ektelestike kai kaname trace
//deutero orisma to onoma tou arxeiou me ton assembly kodika tou arxeiou pou ektelestike
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dict.c"

char * registers [] = { "%eax" , "%ebx" ,"%ecx", "%edx", "%cs", "%ds", "%es", "%fs", "%gs", "%ss","%esi", "%edi" , "%ebp", "%eip" ,"%esp", "%ax", "%bx", "%cx" , "%dx" ,"%ah" ,"%al" ,"%bh" ,"%bl" , "%ch" ,"%dh" ,"%dl" ,"%rax", "%rcx" ,"%rdx" ,"%rbx" ,"%rsp" ,"%rbp" ,"%rsi" ,"%rdi" ,"%sp" ,"%bp" ,"%si" ,"%di" ,"%spl" ,"%bpl" ,"%sil" ,"%dil" , "%ss" ,"%cs" ,"%ds" ,"%es" ,"%fs" ,"%gs" ,"%eflags" ,"%eip","%r8", "%r9","%r10", "%r11", "%r12","%r13", "%r14","%r15","%r8d", "%r9d","%r10d", "%r11d", "%r12d","%r13d", "%r14d","%r15d", "%r8w", "%r9w","%r10w", "%r11w", "%r12w","%r13w", "%r14w","%r15w","%r8b", "%r9b","%r10b", "%r11b", "%r12b" ,"%r13b", "%r14b", "%r15b"}; //size =49

struct Tuple {
    char  *opcode , *arg1 , *arg2 , *arg3 ,*first ,*second, *third;
};

bool StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

bool Isnumber (char *str ){
    for (int i = 0; i < strlen(str); i++) {
        if(!isdigit((str[i]))){return 0;}
        
    }
    return 1;
}

void removeChar(char * str, char charToRemmove){
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++)
    {
        if(str[i] == charToRemmove)
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }
    
}



struct Tuple give_opcode(char *argument, char *line )   //returns the name of the command in our format 
{
  
        //printf("Retrieved line of length %zu:\n") read);
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
        char *arg1 =NULL;
        char *arg2 =NULL;
        char *arg3 =NULL;
        bool arg1reg =false;
        bool arg2reg =false;
        bool arg3reg =false;
        char Delim1[] = ")";
        char Delim2[] = "(";
        char *ptemp1 =NULL;
        char *temporary;

        char temp_first[20]="aa";
        char temp_second[20]="aa";
        char temp_third[20]="aa";
            //strcpy(temp_first, result.first); //copy here the first
            //strcpy(temp_second, result.second); //copy here the second
            //strcpy(temp_third, result.third); //copy here the third
        
        p = strstr(line, argument);
        
        p1 = strtok(p," "); 
        
        p2 =strtok(NULL,"\n"); //periexei tin actuall entoli me kena stin arxi
        
        while (isspace(*p2)){
            ++p2;}             //katharizoume ta kena stin arxi
        //printf("%s \n",  p2); 
        opcode  =strtok(p2,Delimit); //pairnoume to onoma tis entolis
        if (opcode != NULL) {   //pairnoume proto operator
            if((!strcmp(opcode,"long")) ||(!strcmp(opcode,"rep"))  || (!strcmp(opcode,"lock"))  ){
                //ptemp1 = strtok(NULL,Delimit);   
                ptemp1 = strtok(NULL, Delimit);
                strcat(opcode,ptemp1);
                //printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ  concatenated %s into %s \n",ptemp1 ,opcode); 
                }             
            
            op1 = strtok(NULL, Delimit); 
            
            }
        if (op1!= NULL) {       //pairnoume deutero operator
            op2 = strtok(NULL,Delimit); }
        if (op2!= NULL) {       //pairnoume trito operator
            op3= strtok(NULL,Delimit); }

         printf("op1 1is %s \n", op1);
        printf("%s-%s-%s-%s\n",  opcode , op1, op2 ,op3);
        
        //Tsekaroume ama periexoun parentheseis
        //Ama exoun moni parenthesi simainei pos exei kopei kai prepei na petaxtei
        if (op1 !=NULL){
        if (StartsWith(op1, "(") && (strchr(op1, ')') == NULL)){ //parenthesi ( o protos char tote petietai
            op1++;
            printf("the CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC op1 is %s \n", op1);
        }
        else if (((strchr(op1, '(') != NULL) && (strchr(op1, ')') == NULL))){ //parenthesi ( o mesaios char tote kratietai to kommati meta apo parenthesi
             temporary=strtok(op1,Delim2);
             temporary =strtok(NULL," ");
             if(temporary != NULL) strcpy(op1,temporary);
             else {op1=NULL;}
                           
             printf("the BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB op1 is %s \n", op1);
             }
        else if (((strchr(op1, '(') == NULL) && (strchr(op1, ')') != NULL))){ //parenthesi ) stin mesi h telos  tote kratame prin apo parenthesi
             temporary=strtok(op1,Delim1);
             printf("the AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA op1 is %s \n", op1);}
            }

        if (op2 !=NULL){
        if (StartsWith(op2, "(") && (strchr(op2, ')') == NULL)){
            op2++;
            printf("the CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC op2 is %s \n", op2);
        }
        else if (((strchr(op2, '(') != NULL) && (strchr(op2, ')') == NULL))){
             temporary=strtok(op2,Delim2);
             temporary =strtok(NULL," ");
             if(temporary != NULL) {strcpy(op2,temporary);}
             else {op2=NULL;}
                           
             printf("the BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB op2 is %s \n", op2);
             }
        else if (((strchr(op2, '(') == NULL) && (strchr(op2, ')') != NULL))){
             temporary=strtok(op2,Delim1);
             printf("the AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA op2 is %s \n", op2);}
            }

        if (op3 !=NULL){
        if (StartsWith(op3, "(") && (strchr(op3, ')') == NULL)){
            op3++;
            printf("the CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC  op3 is %s \n", op3);
        }
        else if (((strchr(op3, '(') != NULL) && (strchr(op3, ')') == NULL))){
             temporary=strtok(op3,Delim2);
             temporary =strtok(NULL," ");
             if(temporary != NULL) strcpy(op3,temporary);
             else {op3=NULL;}
                           
             printf("the BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB op3 is %s \n", op3);
             }
        else if (((strchr(op3, '(') == NULL) && (strchr(op3, ')') != NULL))){
             temporary=strtok(op3,Delim1);
             printf("the AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA op3 is %s \n", op3);}
            }


        
        //Now starts the categorizing opcodes part
        //first we check if the operators are in the register list
        if (op1!= NULL) {
            //strcpy(temp_first, op1); //copy here the first
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op1))
                    {
                    arg1reg=true;
                    //printf("rgister \n");
                    }
            } 
        }
        if (op2!= NULL) {
            //strcpy(temp_second, op2); //copy here the first
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op2))
                    {
                    arg2reg=true;
                    //printf("rgister \n");
                    }
            } 
        }
        if (op3!= NULL) {
            //strcpy(temp_third, op3); //copy here the first
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op3))
                    {
                    arg3reg=true;
                    //printf("rgister \n");
                    }
            } 
        }


        //Now we do all the checking 

        

         if (op1== NULL) {
            arg1 = "0";
            //strcpy(temp_first, arg1); //copy here the first
         }
         else if(arg1reg){
            arg1 = "r";
         }
         else if ((strchr(op1, '(') != NULL) && (strchr(op1, ')') != NULL))
         {
            arg1 = "m";
         }
         else if(StartsWith(op1, "<") && (strlen(op1) > 2 && !strcmp(op1 + strlen(op1) - strlen(">"), ">"))) //to starts with einai ama arxizei i leski me substring , to deutero kommati einai an teleionei se sugekkrimeno char
         {
            arg1 = "m";
         }
         else if (StartsWith(op1, "%"))
         {
            arg1 = "m";
         }
          else if( (StartsWith(op1, "$0x") )|| (StartsWith(op1, "0x"))   )
         {
            arg1 = "I";
         }
         else if (!strcmp(op1, "%cl"))
         {
            arg1 ="cl";
         }
         else if (Isnumber(op1))
         {
            arg1 = "I";
         }
         else 
         {
            printf("could not find type of %s\n", op1);
            arg1="0";
         }
         
         if (op2== NULL) {
            arg2 = "0";
            //strcpy(temp_second, arg2); //copy here the first
         }
         else if(arg2reg){
            arg2 = "r";
         }
         else if ((strchr(op2, '(') != NULL) && (strchr(op2, ')') != NULL))
         {
            arg2 = "m";
         }
         else if(StartsWith(op2, "<") && (strlen(op2) > 2 && !strcmp(op2 + strlen(op2) - strlen(">"), ">"))) //to starts with einai ama arxizei i leski me substring , to deutero kommati einai an teleionei se sugekkrimeno char
         {
            arg2 = "m";
         }
         else if (StartsWith(op2, "%"))
         {
            arg2 = "m";
         }
          else if( (StartsWith(op2, "$0x") )|| (StartsWith(op2, "0x"))   )
         {
            arg2 = "I";
         }
         else if (!strcmp(op2, "%cl"))
         {
            arg2 ="cl";
         }
         else if (Isnumber(op2))
         {
            arg2 = "I";
         }
         else 
         {
            printf("could not find type of %s\n", op2);
            arg2="0";
         }


        if (op3== NULL) {
            arg3 = "0";
            //strcpy(temp_third, op3); //copy here the first
         }
         else if(arg3reg){
            arg3 = "r";
         }
         else if ((strchr(op3, '(') != NULL) && (strchr(op3, ')') != NULL))
         {
            arg3 = "m";
         }
         else if(StartsWith(op3, "<") && (strlen(op3) > 2 && !strcmp(op3 + strlen(op3) - strlen(">"), ">"))) //to starts with einai ama arxizei i leski me substring , to deutero kommati einai an teleionei se sugekkrimeno char
         {
            arg3 = "m";
         }
         else if (StartsWith(op3, "%"))
         {
            arg3 = "m";
         }
          else if( (StartsWith(op3, "$0x") )|| (StartsWith(op3, "0x"))   )
         {
            arg3 = "I";
         }
         else if (!strcmp(op3, "%cl"))
         {
            arg3 ="cl";
         }
         else if (Isnumber(op3))
         {
            arg3 = "I";
         }
         else 
         {
            printf("could not find type of %s\n", op3);
            arg1="0";
         }
        //printf ("Type of op2 %s is %s \n",op2 ,arg1);
        if(!strcmp(arg2,"0")){
        struct Tuple command = {opcode, arg1,arg2,arg3,  op1, op2 ,op3 }; //exo allaksei seira ton arg1 , arg2 giati otan trexei sto pc einai anapoda
        //printf("%s %s %s %s\n",  opcode , op1, op2 ,op3);
        return command;}
        else {
        struct Tuple command = {opcode, arg2,arg1,arg3, op1, op2 ,op3 }; //exo allaksei seira ton arg1 , arg2 giati otan trexei sto pc einai anapoda
        //printf("%s %s %s %s\n",  opcode , op1, op2 ,op3);
        return command;
        }
    
}
int main(int argc, char *argv[]) {

       dict_t**dict = dictAlloc();



    FILE * fp2;
    char * line2 = NULL;
    size_t len2 = 0;
    ssize_t read2;

    char addr1[20] ="aa"; //address of first rapl function
    char length1[20] ="aa";  //length of first rapl function
    char addr2[20] ="aa";
    char length2[20] ="aa";
    char addr3[20] ="aa";
    char length3[20] ="aa";

    if (argc<3){                //if an argument is not provided then error message and fail 
        printf("You have not given the name of the file where addresses of rapl reads are \n");
        return 1;}
    fp2 = fopen(argv[2], "r");
    if (fp2 == NULL){
        printf("Could not open file with addresses \n");
        exit(EXIT_FAILURE);}
    
    while ((read2 = getline(&line2, &len2, fp2)) != -1) {
        if (strchr(line2, 'A') != NULL){
            //tempor1 = strtok(line2," ");
            //addr1 = strtok(tempor1," ");
            //length1 = strtok(addr1,"\n");  
            char * tempor1 = strtok(line2, " ");
            
            tempor1 = strtok(NULL, " ");
            strcpy(addr1, tempor1);
            tempor1 = strtok(NULL, "\n");
            strcpy(length1, tempor1);

  
        }
        else if (strchr(line2, 'B') != NULL){
            //tempor1 = strtok(line2," ");
            //addr1 = strtok(tempor1," ");
            //length1 = strtok(addr1,"\n");  
            char * tempor2 = strtok(line2, " ");
            
            tempor2 = strtok(NULL, " ");
            strcpy(addr2, tempor2);
            tempor2 = strtok(NULL, "\n");
            strcpy(length2, tempor2);

  
        }
        else if (strchr(line2, 'C') != NULL){
            //tempor1 = strtok(line2," ");
            //addr1 = strtok(tempor1," ");
            //length1 = strtok(addr1,"\n");  
            char * tempor3 = strtok(line2, " ");
            
            tempor3 = strtok(NULL, " ");
            strcpy(addr3, tempor3);
            tempor3 = strtok(NULL, "\n");
            strcpy(length3, tempor3);

  
        }

        
        



        }

        printf("Rapl1 is  %s with length %s  \n",  addr1 , length1  );
        printf("Rapl2 is  %s with length %s  \n",  addr2 , length2  );
        printf("Rapl3 is  %s with length %s  \n",  addr3 , length3  );
      
    

        fclose(fp2);
        if (line2)
        free(line2);





    FILE * fp1;
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    fp1 = fopen("opcodes.txt", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);
    
    while ((read1 = getline(&line1, &len1, fp1)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        
        char *p =NULL ;
        char *p1= NULL ;
        char *ptemp =NULL;
        char *opcode_name;
        opcode_name = malloc(100);
        char *energy;
        energy = malloc(100);
        
        p1 = strtok(line1," ");
        
        //strcpy(p1,p); //periexei to kleidi diladi to opcode
        p = strtok(NULL,"\n");   //periexei tin energeia

        //printf("DDDDDDDDDDDDDDDDDDDDDD %s \n",p1);  
        //printf("EEEEEEEEEEEEEEEEEEEEE %s \n",p); 
        if (opcode_name) {  
        // Always check that the return value of malloc() is not NULL
          // Now you can use the allocated memory
          strcpy(opcode_name, p1);//opcode_name periexei ton opcode
        }
        if (opcode_name) {
        // Always check that the return value of malloc() is not NULL
          // Now you can use the allocated memory
          strcpy(energy, p); //energy periexei tin energeia
        }
        
        //printf("%s %s",p,(p++));
         //printf("%s %s ",p ,p++);
        addItem(dict, opcode_name, energy); //prosthetoume sto leksiko to zeugos energeia opcode
        printf("You entered %s  with key %s \n", (char *)getItem(*dict, opcode_name), opcode_name);
        
    }
    
        
    fclose(fp1);
    if (line1)
        free(line1);
    
    
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
    float rapl_total_weight =0;
    int count_ignore =0 ;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        if ( count_ignore >0){
            printf("Ignored command %d \n", count_ignore);
            count_ignore = count_ignore-1;            
            }
        else{             
            

            struct Tuple result ;
            result =give_opcode(argv[1],line  );
            char temp_first[20]="aa";
            char temp_second[20]="aa";
            char temp_third[20]="aa";
            if(result.first != NULL){ 
            strcpy(temp_first, result.first); //copy here the first
            }
            if(result.second != NULL){ 
            strcpy(temp_second, result.second); //copy here the second
            }
            if(result.third != NULL){ 
            strcpy(temp_third, result.third); //copy here the third
            }
            

            if ((!strcmp(temp_first, addr1))|| (!strcmp(temp_second, addr1)) || (!strcmp(temp_third, addr1)) ){
                printf("We have found a rapl1 command \n");
                count_ignore = atoi(length1);
                printf("FFFFFFFFFFFFFFFFFFFFFFFF the weight of bb are %f \n", rapl_total_weight);
                rapl_total_weight=0;
                }
            else if ((!strcmp(temp_first, addr2))|| (!strcmp(temp_second, addr2)) || (!strcmp(temp_third, addr2)) ){
                printf("We have found a rapl2 command \n");
                count_ignore = atoi(length2);
                printf("FFFFFFFFFFFFFFFFFFFFFFFF the weight of bb are %f \n", rapl_total_weight);
                rapl_total_weight=0;
                }
            else if ((!strcmp(temp_first, addr3))|| (!strcmp(temp_second, addr3)) || (!strcmp(temp_third, addr3)) ){
                printf("We have found a rapl3 command \n");
                count_ignore = atoi(length3);
                printf("FFFFFFFFFFFFFFFFFFFFFFFF the weight of bb are %f \n", rapl_total_weight);
                rapl_total_weight=0;
                }
            else{


                printf("Result is %s %s %s %s \n",  result.opcode , result.arg1, result.arg2, result.arg3 );
                printf("Result is GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  %s %s %s %s \n",  result.opcode , result.first, result.second, result.third );


                //Now we will create all possible variations of opcodes+ operands
                char result000[20] ="aa";
                char result001[20]="aa";
                char result010[20]="aa";
                char result011[20]="aa";
                char result100[20]="aa";
                char result101[20]="aa";
                char result110[20]="aa";
                char result111[20]="aa";

                char result000_cut[20] ="aa"; // the opcode without last char
                char result001_cut[20]="aa";
                char result010_cut[20]="aa";
                char result011_cut[20]="aa";
                char result100_cut[20]="aa";
                char result101_cut[20]="aa";
                char result110_cut[20]="aa";
                char result111_cut[20]="aa";

                char result000_cut2[20] ="aa"; //the opcode without 2 last chars
                char result001_cut2[20]="aa";
                char result010_cut2[20]="aa";
                char result011_cut2[20]="aa";
                char result100_cut2[20]="aa";
                char result101_cut2[20]="aa";
                char result110_cut2[20]="aa";
                char result111_cut2[20]="aa";

                char result000_cut3[20] ="aa"; //the opcode without 3 last chars
                char result001_cut3[20]="aa";
                char result010_cut3[20]="aa";
                char result011_cut3[20]="aa";
                char result100_cut3[20]="aa";
                char result101_cut3[20]="aa";
                char result110_cut3[20]="aa";
                char result111_cut3[20]="aa";

            
            
                strcpy(result000, result.opcode); //copy here the opcode
                strcpy(result001, result.opcode);
                strcpy(result010, result.opcode);
                strcpy(result011, result.opcode);
                strcpy(result100, result.opcode);
                strcpy(result101, result.opcode);
                strcpy(result110, result.opcode);
                strcpy(result111, result.opcode);

                strcpy(result000_cut, result.opcode); //copy here the opcode
                strcpy(result001_cut, result.opcode);
                strcpy(result010_cut, result.opcode);
                strcpy(result011_cut, result.opcode);
                strcpy(result100_cut, result.opcode);
                strcpy(result101_cut, result.opcode);
                strcpy(result110_cut, result.opcode);
                strcpy(result111_cut, result.opcode);

                result000_cut[strlen(result000_cut)-1] = '\0';  //remove last char
                result001_cut[strlen(result001_cut)-1] = '\0';
                result010_cut[strlen(result010_cut)-1] = '\0';
                result011_cut[strlen(result011_cut)-1] = '\0';
                result100_cut[strlen(result100_cut)-1] = '\0';
                result101_cut[strlen(result101_cut)-1] = '\0';
                result110_cut[strlen(result110_cut)-1] = '\0';
                result111_cut[strlen(result111_cut)-1] = '\0';

                strcpy(result000_cut2, result000_cut); //copy here the opcode without last char
                strcpy(result001_cut2, result000_cut);
                strcpy(result010_cut2, result000_cut);
                strcpy(result011_cut2, result000_cut);
                strcpy(result100_cut2, result000_cut);
                strcpy(result101_cut2, result000_cut);
                strcpy(result110_cut2, result000_cut);
                strcpy(result111_cut2, result000_cut);

                result000_cut2[strlen(result000_cut2)-1] = '\0';  //remove last char so 2 now removed
                result001_cut2[strlen(result001_cut2)-1] = '\0';
                result010_cut2[strlen(result010_cut2)-1] = '\0';
                result011_cut2[strlen(result011_cut2)-1] = '\0';
                result100_cut2[strlen(result100_cut2)-1] = '\0';
                result101_cut2[strlen(result101_cut2)-1] = '\0';
                result110_cut2[strlen(result110_cut2)-1] = '\0';
                result111_cut2[strlen(result111_cut2)-1] = '\0';

                strcpy(result000_cut3, result000_cut2);  //copy here the opcode without  2 last chars
                strcpy(result001_cut3, result000_cut2);
                strcpy(result010_cut3, result000_cut2);
                strcpy(result011_cut3, result000_cut2);
                strcpy(result100_cut3, result000_cut2);
                strcpy(result101_cut3, result000_cut2);
                strcpy(result110_cut3, result000_cut2);
                strcpy(result111_cut3, result000_cut2);

                result000_cut3[strlen(result000_cut3)-1] = '\0'; //remove last char so 3 now removed
                result001_cut3[strlen(result001_cut3)-1] = '\0';
                result010_cut3[strlen(result010_cut3)-1] = '\0';
                result011_cut3[strlen(result011_cut3)-1] = '\0';
                result100_cut3[strlen(result100_cut3)-1] = '\0';
                result101_cut3[strlen(result101_cut3)-1] = '\0';
                result110_cut3[strlen(result110_cut3)-1] = '\0';
                result111_cut3[strlen(result111_cut3)-1] = '\0';

                

                //Create the 8 different combos for the string opcode
                strcat(result000,"_0_0_0");
                
                strcat(result001,"_0_0_");
                strcat(result001,result.arg3);

                strcat(result010,"_0_");
                strcat(result010,result.arg2);
                strcat(result010,"_0");

                strcat(result011,"_0_");
                strcat(result011,result.arg2);
                strcat(result011,"_");
                strcat(result011,result.arg3);

                strcat(result100,"_");
                strcat(result100,result.arg1);
                strcat(result100,"_0_0");

                strcat(result101,"_");
                strcat(result101,result.arg1);
                strcat(result101,"_0_");
                strcat(result101,result.arg3);

                strcat(result110,"_");
                strcat(result110,result.arg1);
                strcat(result110,"_");
                strcat(result110,result.arg2);
                strcat(result110,"_0");

                strcat(result111,"_");
                strcat(result111,result.arg1);
                strcat(result111,"_");
                strcat(result111,result.arg2);
                strcat(result111,"_");
                strcat(result111,result.arg3);


                //Create the 8 different combos for the string with missing last  char
                strcat(result000_cut,"_0_0_0");
                
                strcat(result001_cut,"_0_0_");
                strcat(result001_cut,result.arg3);

                strcat(result010_cut,"_0_");
                strcat(result010_cut,result.arg2);
                strcat(result010_cut,"_0");

                strcat(result011_cut,"_0_");
                strcat(result011_cut,result.arg2);
                strcat(result011_cut,"_");
                strcat(result011_cut,result.arg3);

                strcat(result100_cut,"_");
                strcat(result100_cut,result.arg1);
                strcat(result100_cut,"_0_0");

                strcat(result101_cut,"_");
                strcat(result101_cut,result.arg1);
                strcat(result101_cut,"_0_");
                strcat(result101_cut,result.arg3);

                strcat(result110_cut,"_");
                strcat(result110_cut,result.arg1);
                strcat(result110_cut,"_");
                strcat(result110_cut,result.arg2);
                strcat(result110_cut,"_0");

                strcat(result111_cut,"_");
                strcat(result111_cut,result.arg1);
                strcat(result111_cut,"_");
                strcat(result111_cut,result.arg2);
                strcat(result111_cut,"_");
                strcat(result111_cut,result.arg3);

                //Create the 8 different combos for the string with missing last 2 chars
                strcat(result000_cut2,"_0_0_0");
                
                
                strcat(result001_cut2,"_0_0_");
                strcat(result001_cut2,result.arg3);

                strcat(result010_cut2,"_0_");
                strcat(result010_cut2,result.arg2);
                strcat(result010_cut2,"_0");

                strcat(result011_cut2,"_0_");
                strcat(result011_cut2,result.arg2);
                strcat(result011_cut2,"_");
                strcat(result011_cut2,result.arg3);

                strcat(result100_cut2,"_");
                strcat(result100_cut2,result.arg1);
                strcat(result100_cut2,"_0_0");

                strcat(result101_cut2,"_");
                strcat(result101_cut2,result.arg1);
                strcat(result101_cut2,"_0_");
                strcat(result101_cut2,result.arg3);

                strcat(result110_cut2,"_");
                strcat(result110_cut2,result.arg1);
                strcat(result110_cut2,"_");
                strcat(result110_cut2,result.arg2);
                strcat(result110_cut2,"_0");

                strcat(result111_cut2,"_");
                strcat(result111_cut2,result.arg1);
                strcat(result111_cut2,"_");
                strcat(result111_cut2,result.arg2);
                strcat(result111_cut2,"_");
                strcat(result111_cut2,result.arg3);


                //Create the 8 different combos for the string with missing last 3 chars
                strcat(result000_cut3,"_0_0_0");
                
                
                strcat(result001_cut3,"_0_0_");
                strcat(result001_cut3,result.arg3);

                strcat(result010_cut3,"_0_");
                strcat(result010_cut3,result.arg2);
                strcat(result010_cut3,"_0");

                strcat(result011_cut3,"_0_");
                strcat(result011_cut3,result.arg2);
                strcat(result011_cut3,"_");
                strcat(result011_cut3,result.arg3);

                strcat(result100_cut3,"_");
                strcat(result100_cut3,result.arg1);
                strcat(result100_cut3,"_0_0");

                strcat(result101_cut3,"_");
                strcat(result101_cut3,result.arg1);
                strcat(result101_cut3,"_0_");
                strcat(result101_cut3,result.arg3);

                strcat(result110_cut3,"_");
                strcat(result110_cut3,result.arg1);
                strcat(result110_cut3,"_");
                strcat(result110_cut3,result.arg2);
                strcat(result110_cut3,"_0");

                strcat(result111_cut3,"_");
                strcat(result111_cut3,result.arg1);
                strcat(result111_cut3,"_");
                strcat(result111_cut3,result.arg2);
                strcat(result111_cut3,"_");
                strcat(result111_cut3,result.arg3);

                //here starts
                //printf("Result 000 is %s \n ",result000 );    
                //printf("Result 001 is %s \n ",result001 );
                //printf("Result 010 is %s \n ",result010 );
                //printf("Result 011 is %s \n ",result011 );
                //printf("Result 100 is %s \n ",result100 );
                //printf("Result 101 is %s \n ",result101 );
                //printf("Result 110 is %s \n ",result110 );
                //printf("Result 111 is %s \n ",result111 );
                //printf("Result 000 is %s \n ",result000 );

                //printf("Result 000_cut is %s \n ",result000_cut );    
                //printf("Result 001_cut is %s \n ",result001_cut );
                //printf("Result 010_cut is %s \n ",result010_cut );
                //printf("Result 011_cut is %s \n ",result011_cut );
                //printf("Result 100_cut is %s \n ",result100_cut );
                //printf("Result 101_cut is %s \n ",result101_cut );
                //printf("Result 110_cut is %s \n ",result110_cut );
                //printf("Result 111_cut is %s \n ",result111_cut );
                //printf("Result 000_cut is %s \n ",result000_cut );
                //here ends
            
                char *value ; 

                if ((char *)getItem(*dict, result000) != NULL ) {
                    value =(char *)getItem(*dict, result000) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-000 %s of %s \n", result000, value);
                }
                
                else if ((char *)getItem(*dict, result001) != NULL ) {
                    value =(char *)getItem(*dict, result001) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-001 %s of %s \n", result001, value);
                }
                else if ((char *)getItem(*dict, result010) != NULL ) {
                    value =(char *)getItem(*dict, result010) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-010 %s of %s \n", result010, value);
                }
                else if ((char *)getItem(*dict, result011) != NULL ) {
                    value =(char *)getItem(*dict, result011) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-011 %s of %s \n", result011, value);
                }
                else if ((char *)getItem(*dict, result100) != NULL ) {
                    value =(char *)getItem(*dict, result100) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-100 %s of %s \n", result100, value);
                }
                else if ((char *)getItem(*dict, result101) != NULL ) {
                    value =(char *)getItem(*dict, result101) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-101 %s of %s \n", result101, value);
                }
                else if ((char *)getItem(*dict, result110) != NULL ) {
                    value =(char *)getItem(*dict, result110) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-110 %s of %s \n", result110, value);
                }
                else if ((char *)getItem(*dict, result111) != NULL ) {
                    value =(char *)getItem(*dict, result111) ;
                    rapl_total_weight+=atof(value);
                    printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-111 %s of %s \n", result111, value);
                }
                else{
                    if ((char *)getItem(*dict, result000_cut) != NULL ) {
                        value =(char *)getItem(*dict, result000_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX-000 %s of %s \n", result000_cut, value);
                    }
                    
                    else if ((char *)getItem(*dict, result001_cut) != NULL ) {
                        value =(char *)getItem(*dict, result001_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-001 %s of %s \n", result001_cut, value);
                    }
                    else if ((char *)getItem(*dict, result010_cut) != NULL ) {
                        value =(char *)getItem(*dict, result010_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-010 %s of %s \n", result010_cut, value);
                    }
                    else if ((char *)getItem(*dict, result011_cut) != NULL ) {
                        value =(char *)getItem(*dict, result011_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-011 %s of %s \n", result011_cut, value);
                    }
                    else if ((char *)getItem(*dict, result100_cut) != NULL ) {
                        value =(char *)getItem(*dict, result100_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-100 %s of %s \n", result100_cut, value);
                    }
                    else if ((char *)getItem(*dict, result101_cut) != NULL ) {
                        value =(char *)getItem(*dict, result101_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-101 %s of %s \n", result101_cut, value);
                    }
                    else if ((char *)getItem(*dict, result110_cut) != NULL ) {
                        value =(char *)getItem(*dict, result110_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-110 %s of %s \n", result110_cut, value);
                    }
                    else if ((char *)getItem(*dict, result111_cut) != NULL ) {
                        value =(char *)getItem(*dict, result111_cut) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-111 %s of %s \n", result111_cut, value);
                    }
                    else{
                        if ((char *)getItem(*dict, result000_cut2) != NULL ) {
                        value =(char *)getItem(*dict, result000_cut2) ;
                        rapl_total_weight+=atof(value);
                        printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX-000 %s of %s \n", result000_cut2, value);
                        }
                
                        else if ((char *)getItem(*dict, result001_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result001_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-001 %s of %s \n", result001_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result010_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result010_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-010 %s of %s \n", result010_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result011_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result011_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-011 %s of %s \n", result011_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result100_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result100_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-100 %s of %s \n", result100_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result101_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result101_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-101 %s of %s \n", result101_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result110_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result110_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-110 %s of %s \n", result110_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result111_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result111_cut2) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-111 %s of %s \n", result111_cut2, value);
                        }
                        else{
                            
                            if ((char *)getItem(*dict, result000_cut3) != NULL ) {
                            value =(char *)getItem(*dict, result000_cut3) ;
                            rapl_total_weight+=atof(value);
                            printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX-000 %s of %s \n", result000_cut3, value);
                            }
                
                            else if ((char *)getItem(*dict, result001_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result001_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-001 %s of %s \n", result001_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result010_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result010_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-010 %s of %s \n", result010_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result011_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result011_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-011 %s of %s \n", result011_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result100_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result100_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-100 %s of %s \n", result100_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result101_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result101_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-101 %s of %s \n", result101_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result110_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result110_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-110 %s of %s \n", result110_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result111_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result111_cut3) ;
                                rapl_total_weight+=atof(value);
                                printf("Added %f to value %f \n", rapl_total_weight, atof(value));
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX-111 %s of %s \n", result111_cut3, value);
                            }
                            else{
                                if (!strcmp(result.opcode,"syscall") ){printf("We had a Syscall \n");} // see what to add for these
                                else{
                                    printf("i cannot  find opcode %s or %s or %s or %s  \n",result000 ,result000_cut, result000_cut2, result000_cut3);}
                            }
                        }
                    }
                } 
                printf("Value is SDSDSDSD %s \n",value);
            }
        
        }
    }

      
    

        fclose(fp);
        if (line)
        free(line);
    exit(EXIT_SUCCESS);
    
    
    return 0;
}

