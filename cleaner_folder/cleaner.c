//Auto einai ena script to opoio trexoume pano sto trace tou kodika pou exei perasei idi apo to pass mas 
//proto orisma to onoma tou arxeiou pou ektelestike kai kaname trace
//deutero orisma to onoma tou arxeiou me ton assembly kodika tou arxeiou pou ektelestike
//pempto onoma opou apothikeuontai ta command opcodes pou dn brethikan sto leksiko
//ekto onoma pou leei dieuthinseis ton rapl addresse
//teksto san ./cleaner a_static opcodes.txt >>output.txt 2>log.txt

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../dict/dict.c" //here the custom dictionary we use to store the opcode energy values

char * registers [] = { "%eax" , "%ebx" ,"%ecx", "%edx", "%cs", "%ds", "%es", "%fs", "%gs", "%ss","%esi", "%edi" , "%ebp", "%eip" ,"%esp", "%ax", "%bx", "%cx" , "%dx" ,"%ah" ,"%al" ,"%bh" ,"%bl" , "%ch" ,"%dh" ,"%dl" ,"%rax", "%rcx" ,"%rdx" ,"%rbx" ,"%rsp" ,"%rbp" ,"%rsi" ,"%rdi" ,"%sp" ,"%bp" ,"%si" ,"%di" ,"%spl" ,"%bpl" ,"%sil" ,"%dil" , "%ss" ,"%cs" ,"%ds" ,"%es" ,"%fs" ,"%gs" ,"%eflags" ,"%eip","%r8", "%r9","%r10", "%r11", "%r12","%r13", "%r14","%r15","%r8d", "%r9d","%r10d", "%r11d", "%r12d","%r13d", "%r14d","%r15d", "%r8w", "%r9w","%r10w", "%r11w", "%r12w","%r13w", "%r14w","%r15w","%r8b", "%r9b","%r10b", "%r11b", "%r12b" ,"%r13b", "%r14b", "%r15b"}; //size =49
// the register list contains the possible names for all registers

struct Tuple { // this is a custom struct that contains for every instruction the opcode and the name and type of its arguments
    char  *opcode , *command_address ,*arg1 , *arg2 , *arg3 ,*first ,*second, *third  ;
    char total[100];
};

bool StartsWith(const char *a, const char *b)  //function that returns true if a string contains another string at its starnt
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

bool Isnumber (char *str ){  //function that returns true if a string is a number
    for (int i = 0; i < strlen(str); i++) {
        if(!isdigit((str[i]))){return 0;}
        
    }
    return 1;
}

void removeChar(char * str, char charToRemmove){ //string that removes a char from a string
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



struct Tuple give_opcode(char *argument, char *line )   //returns for an instruction the name of opcode and name and type of its arguments
{
  
        char *p = NULL;
        char *p_address = NULL;
        char p_address_helper[200] = "";
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
        char temp_total[100]="aa";
       
        strcpy(p_address_helper,line);
        p_address= strtok(p_address_helper, ":"); //split it there
        p_address= strtok(NULL, " "); //split it there to get address of command
        
        p = strstr(line, argument); //return a pointer at the first occurence of argument in line
        
        p1 = strtok(p," ");  //split the first irrelevant info
        
        p2 =strtok(NULL,"\n"); //periexei tin actuall entoli me kena stin arxi
        
        while (isspace(*p2)){
            ++p2;}             //katharizoume ta kena stin arxi
        
        
        strcpy(temp_total,p2);//kratao tin entoli
        
        opcode  =strtok(p2,Delimit); //pairnoume to onoma tis entolis dld to opcode 
        if (opcode != NULL) {   //pairnoume proto operator 
            if((!strcmp(opcode,"long")) ||(!strcmp(opcode,"rep"))  || (!strcmp(opcode,"lock"))  )
                {  //an to opcode einai ena apo auta tote to opcode periexei kai tin epomeni leksi
                ptemp1 = strtok(NULL, Delimit);
                strcat(opcode,ptemp1); //ara prosthetoume sto opcode kai tin deuteri leksi
                }
            
            if((!strcmp(opcode,"bnd")) ||(!strcmp(opcode,"repne"))  )
                {  //an to opcode einai ena apo auta tote to opcode periexei mono tin epomeni leksi
                ptemp1 = strtok(NULL, Delimit);
                strcpy(opcode,ptemp1); //ara prosthetoume sto opcode mono tin deuteri leksi
                }             
            
            op1 = strtok(NULL, Delimit);  //protos operator
            
            }
        if (op1!= NULL) {       //pairnoume deutero operator
            op2 = strtok(NULL,Delimit); }
        
        if (op2!= NULL) {       //pairnoume trito operator
            op3= strtok(NULL,Delimit); }
        
        //Tsekaroume ama periexoun parentheseis
        //Ama exoun moni parenthesi simainei pos exei kopei kai prepei na petaxtei
        if (op1 !=NULL)
            {
            if (StartsWith(op1, "(") && (strchr(op1, ')') == NULL))
                { //parenthesi ( o protos char tote petietai
                op1++;
                }
            else if (((strchr(op1, '(') != NULL) && (strchr(op1, ')') == NULL)))
                { //parenthesi ( o mesaios char tote kratietai to kommati meta apo parenthesi
                temporary=strtok(op1,Delim2);
                temporary =strtok(NULL," ");
                if(temporary != NULL) strcpy(op1,temporary);
                else {op1=NULL;}
                }
            else if (((strchr(op1, '(') == NULL) && (strchr(op1, ')') != NULL)))
                { //parenthesi ) stin mesi h telos  tote kratame prin apo parenthesi
                temporary=strtok(op1,Delim1);
                }
            }

        if (op2 !=NULL)
            { //antistoixa gia op2 katharizoume parentheseis
            if (StartsWith(op2, "(") && (strchr(op2, ')') == NULL))
                {   
                op2++;
                }
            else if (((strchr(op2, '(') != NULL) && (strchr(op2, ')') == NULL)))
                {
                temporary=strtok(op2,Delim2);
                temporary =strtok(NULL," ");
                if(temporary != NULL) {strcpy(op2,temporary);}
                else {op2=NULL;}
                }
            else if (((strchr(op2, '(') == NULL) && (strchr(op2, ')') != NULL)))
                {
                temporary=strtok(op2,Delim1);
                }
            }

        if (op3 !=NULL)
            { //antistoixa gia op3 katharizoume parentheseis
            if (StartsWith(op3, "(") && (strchr(op3, ')') == NULL))
                {
                op3++;
                }
            else if (((strchr(op3, '(') != NULL) && (strchr(op3, ')') == NULL)))
                {
                temporary=strtok(op3,Delim2);
                temporary =strtok(NULL," ");
                if(temporary != NULL) strcpy(op3,temporary);
                else {op3=NULL;}
                }
            else if (((strchr(op3, '(') == NULL) && (strchr(op3, ')') != NULL)))
                {
                temporary=strtok(op3,Delim1);
                }
            }


        
        //Now starts the categorizing opcodes part
        //first we check if the operators are in the register list
        if (op1!= NULL) {
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op1))
                    {
                    arg1reg=true;
                    }
            } 
        }
        //same for the second operator
        if (op2!= NULL) {
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op2))
                    {
                    arg2reg=true;
                    }
            } 
        }
        //same for the third operator
        if (op3!= NULL) {
            for(int i = 0; i < 82; ++i)
            {
                if(!strcmp(registers[i], op3))
                    {
                    arg3reg=true;
                    }
            } 
        }


        //Now we do all the checking 

        

         if (op1== NULL)  //an o operator einai kenos bazo san argument 0
         {
            arg1 = "0";
         }
         else if(arg1reg) //an arg1reg einai true tote apo prin eixame dei pos o operator anoikei se lista apo registers
         {
            arg1 = "r";
         }
         else if ((strchr(op1, '(') != NULL) && (strchr(op1, ')') != NULL)) //an exoume anoigma kai kleisimo parenthesis tote prokeitai gia mnimi
         {
            arg1 = "m";
         }
         else if(StartsWith(op1, "<") && (strlen(op1) > 2 && !strcmp(op1 + strlen(op1) - strlen(">"), ">"))) //to starts with einai ama arxizei i leski me substring , to deutero kommati einai an teleionei se sugekkrimeno char
         {
            arg1 = "m";
         }
         else if (StartsWith(op1, "%")) //an arxizei me % tote einai memmory
         {
            arg1 = "m";
         }
          else if( (StartsWith(op1, "$0x") )|| (StartsWith(op1, "0x"))   ) //an arxizei me S0x or Ox tote einai imediate
         {
            arg1 = "I";
         }
         else if (!strcmp(op1, "%cl")) //an einai cl tote einai o register cl
         {
            arg1 ="cl";
         }
         else if (Isnumber(op1)) //an einai sketos arithmos tote einai imediate
         {
            arg1 = "I";
         }
         else 
         {
            fprintf(stderr,"could not find type of %s\n", op1); //an dn mporei na to antistoixisei me kanenan apo autous tous typous apla bazei 0
            arg1="0";
         }
         
         //kanoume tin idia diadikasia gia ton operator 2
         if (op2== NULL) 
         {
            arg2 = "0";
         }
         else if(arg2reg)
         {
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
            fprintf(stderr,"could not find type of %s\n", op2);
            arg2="0";
         }


        if (op3== NULL) { //kanoume tin idia diadikasia gia ton operator 3
            arg3 = "0";
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
            fprintf(stderr,"could not find type of %s\n", op3);
            arg1="0";
         }
        
        if(!strcmp(arg2,"0"))
            { //ama den exoume arg2 tote ta epistrefoume me tin seira tin kanoniki
            struct Tuple command = {opcode,p_address, arg1,arg2,arg3,  op1, op2 ,op3 ," "}; 
            strcpy(command.total, temp_total); //epistrefo kai tin entoli olokliti
            return command;
            }
        else 
            {//ama exoume arg2 kanonika
            struct Tuple command = {opcode,p_address, arg2,arg1,arg3, op2, op1 ,op3 ," "}; //exo allaksei seira ton arg1 , arg2 giati otan trexei sto pc einai anapoda
            strcpy(command.total, temp_total); //epistrefo kai tin entoli olokliri
            return command;
            }
    
}

int main(int argc, char *argv[]) {
    dict_t**dict = dictAlloc(); //orizo to leksiko pou tha xrisimopoiso


    //MAIN PART 1 :find addresses of rapl function calls
    FILE * fp2;
    char * line2 = NULL;
    size_t len2 = 0;
    ssize_t read2;

    FILE * fp3;
    char * line3 = NULL;
    size_t len3 = 0;
    ssize_t read3;
    

    
    char addr1[20] ="00000"; //address of first rapl function
    char addr1_fin[20] ="0";  //length of first rapl function
    char addr2[20] ="00000";
    char addr2_fin[20] ="0";
    char addr3[20] ="00000";
    char addr3_fin[20] ="0";

    if (argc<5)
        {    //if an argument is not provided then error message and fail 
         fprintf(stderr,"this is first %s \n", argv[1]);
        fprintf(stderr,"You have not given all the 5 arguments \n");
        fprintf(stderr,"1) the name of the file where the addresses for rapl reads are stores \n 2) the name of executed file that has been traced command \n 3) the trace input file\n 4) opcode file txt \n 5)the file where misiing opcodes will be stored");
        return 1;
        }
    fp2 = fopen(argv[2], "r"); //to deutero argument einai to onoma tou arxeiou me tis rapl addresses
    if (fp2 == NULL)
        {
        fprintf(stderr,"Could not open file with addresses \n");
        exit(EXIT_FAILURE);
        }
    
    while ((read2 = getline(&line2, &len2, fp2)) != -1) 
        {
        if (strchr(line2, 'A') != NULL) //A einai to proto rapl read
            {
            char * tempor1 = strtok(line2, " ");
            tempor1 = strtok(NULL, " ");
            strcpy(addr1, tempor1);
            tempor1 = strtok(NULL, "\n");
            strcpy(addr1_fin, tempor1);
            }
        else if (strchr(line2, 'B') != NULL) //B einai to deutero rapl read
            { 
            char * tempor2 = strtok(line2, " ");
            tempor2 = strtok(NULL, " ");
            strcpy(addr2, tempor2);
            tempor2 = strtok(NULL, "\n");
            strcpy(addr2_fin, tempor2);
            }
        else if (strchr(line2, 'C') != NULL) //C einai to trito rapl read
            { 
            char * tempor3 = strtok(line2, " ");
            tempor3 = strtok(NULL, " ");
            strcpy(addr3, tempor3);
            tempor3 = strtok(NULL, "\n");
            strcpy(addr3_fin, tempor3);
            }
        }
    

    fprintf(stderr,"Rapl1 is  %s with last addr %s  \n",  addr1 , addr1_fin  );
    fprintf(stderr,"Rapl2 is  %s with last addr %s  \n",  addr2 , addr2_fin );
    fprintf(stderr,"Rapl3 is  %s with last addr %s  \n",  addr3 , addr3_fin  );
      
    
    fclose(fp2);
    if (line2)
    free(line2);


    //MAIN PART 2: read opcodes enrgy and create dictionary 
    FILE * fp1;
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    fp1 = fopen(argv[4], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr,"Could not open file with opcodes \n");
        exit(EXIT_FAILURE);
    }
    

    fp3 = fopen("missing_opcodes.txt", "w+");
    if (fp3 == NULL)
    {
        fprintf(stderr,"Could not open file with opcodes \n");
        exit(EXIT_FAILURE);
    }
    while ((read1 = getline(&line1, &len1, fp1)) != -1)     
        {
        char *p =NULL ;
        char *p1= NULL ;
        char *ptemp =NULL;
        char *opcode_name;
        opcode_name = malloc(100);
        char *energy;
        energy = malloc(100);
        
        p1 = strtok(line1," ");  //periexei to opcode
        p = strtok(NULL,"\n");   //periexei tin energeia

        if (opcode_name) 
            {  
            // Always check that the return value of malloc() is not NULL
            // Now you can use the allocated memory
            strcpy(opcode_name, p1);//opcode_name periexei ton opcode
            }

        if (energy) 
            {
            // Always check that the return value of malloc() is not NULL
            // Now you can use the allocated memory
            strcpy(energy, p); //energy periexei tin energeia
            }
        
        addItem(dict, opcode_name, energy); //prosthetoume sto leksiko to zeugos energeia opcode
        fprintf(stderr,"You entered %s  with key %s \n", (char *)getItem(*dict, opcode_name), opcode_name);
        
    }
    
        
    fclose(fp1);
    if (line1)
        free(line1);
    
    
    //MAIN PART 3: read trace and find types of commands and correspond them to energy

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(argv[3], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    if (argc<4)
        {  //if the name of file run is not provided then error message and fail 
        fprintf(stderr,"You have not given the name of the file that was executed \n");
        return 1;
        }
    else
        {
        strcat(argv[1] ,") ");   //this will be the telling where the gerbage stops and where actuall commands start
        }

    float rapl_total_weight =0; //total weight of BB so far
    bool ignore =false ; // how many instructions we should ignore after rapl read
    float temp_value =0;

    while ((read = getline(&line, &len, fp)) != -1) 
        {
        if ( ignore ) //ama auti einai entoli pou prepei na agnoisoume epeidi einai mesa se rapl read function
            {
            char *ignore_address = NULL;
            char ignore_address_helper[200] = "";
            strcpy(ignore_address_helper,line);
            ignore_address= strtok(ignore_address_helper, ":"); //split it there
            ignore_address= strtok(NULL, " ");
            //printf("Ignore addres is +%s+ vs +%s+\n", ignore_address ,addr1_fin );
            if ((!strcmp(ignore_address, addr1_fin)) || (!strcmp(ignore_address, addr2_fin)) || (!strcmp(ignore_address, addr3_fin)))
                {
                    //printf("###############\n");
                    ignore =false;
                }
                      
            }
        else{   //kanoniki entoli pou prepei na metrisoume
            struct Tuple result ;
            
            result =give_opcode(argv[1],line  ); //kloume tin sunartisi gia na mas dosei to opcode tis entolis tous operator ris kai tous tupous tous
            char temp_first[20]="aa";
            char temp_second[20]="aa";
            char temp_third[20]="aa";
            char temp_total[100]="aa";
            char command_ad[100]="aa";
            

            if(result.first != NULL)
                { 
            strcpy(temp_first, result.first); //copy here the first
                }
            if(result.second != NULL)
                { 
            strcpy(temp_second, result.second); //copy here the second
                }
            if(result.third != NULL)
                { 
            strcpy(temp_third, result.third); //copy here the third
                }
            if((strcmp(result.total," ") !=0)) 
                { 
            strcpy(temp_total, result.total); //copy here the total
                }
            
            if(result.command_address != NULL) 
                { 
            strcpy(command_ad, result.command_address); //copy here the address of the command
                }
           
            //if ((!strcmp(temp_first, addr1))|| (!strcmp(temp_second, addr1)) || (!strcmp(temp_third, addr1)) ) //if it contains the addr for rapl1 call then this is rapl instruction
            if (!strcmp(command_ad, addr1)) 
                {
                ignore = true; //poses entoles prepei na kanoume ignore
                printf("+\nA___________ @%f", rapl_total_weight-temp_value); //rapl read 1
                //printf("\n%s",temp_total);//ektiponoume tin proti entoli tou neu basic object
                rapl_total_weight=0;
                }
            //else if ((!strcmp(temp_first, addr2))|| (!strcmp(temp_second, addr2)) || (!strcmp(temp_third, addr2)) )
            else if (!strcmp(command_ad, addr2)) 
                {
                printf("+\nB__________ @%f", rapl_total_weight-temp_value); //rapl read 2
                //printf("\n%s",temp_total);//ektiponoume tin proti entoli tou neu basic object
                ignore = true;
                rapl_total_weight=0;
                }
            //else if ((!strcmp(temp_first, addr3))|| (!strcmp(temp_second, addr3)) || (!strcmp(temp_third, addr3)) )
            else if (!strcmp(command_ad, addr3)) 
                {
                printf("+\nC__________ @%f", rapl_total_weight-temp_value); //rapl read 3
                //printf("\n%s",temp_total);//ektiponoume tin proti entoli tou neu basic object
                ignore = true;
                rapl_total_weight=0;
                }
            else{ //periptosi kanonikis entolis oxi rapl read

                printf("\n%s",temp_total);
                //strcpy(temp_total_prev, temp_total);
               
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

            
                char *value ; 

                if ((char *)getItem(*dict, result000) != NULL ) {
                    value =(char *)getItem(*dict, result000) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=000 %s of %s \n", result000, value);
                }
                
                else if ((char *)getItem(*dict, result001) != NULL ) {
                    value =(char *)getItem(*dict, result001) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=001 %s of %s \n", result001, value);
                }
                else if ((char *)getItem(*dict, result010) != NULL ) {
                    value =(char *)getItem(*dict, result010) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=010 %s of %s \n", result010, value);
                }
                else if ((char *)getItem(*dict, result011) != NULL ) {
                    value =(char *)getItem(*dict, result011) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=011 %s of %s \n", result011, value);
                }
                else if ((char *)getItem(*dict, result100) != NULL ) {
                    value =(char *)getItem(*dict, result100) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=100 %s of %s \n", result100, value);
                }
                else if ((char *)getItem(*dict, result101) != NULL ) {
                    value =(char *)getItem(*dict, result101) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=101 %s of %s \n", result101, value);
                }
                else if ((char *)getItem(*dict, result110) != NULL ) {
                    value =(char *)getItem(*dict, result110) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=110 %s of %s \n", result110, value);
                }
                else if ((char *)getItem(*dict, result111) != NULL ) {
                    value =(char *)getItem(*dict, result111) ;
                    temp_value = atof(value);
                    rapl_total_weight+=temp_value;
                    printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=111 %s of %s \n", result111, value);
                }
                else{
                    if ((char *)getItem(*dict, result000_cut) != NULL ) {
                        value =(char *)getItem(*dict, result000_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                    //printf("total is %f\n",rapl_total_weight);
                    //printf("VALUE IS XXXXXXXXXXXXXXXXXX=000 %s of %s \n", result000_cut, value);
                    }
                    
                    else if ((char *)getItem(*dict, result001_cut) != NULL ) {
                        value =(char *)getItem(*dict, result001_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=001 %s of %s \n", result001_cut, value);
                    }
                    else if ((char *)getItem(*dict, result010_cut) != NULL ) {
                        value =(char *)getItem(*dict, result010_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=010 %s of %s \n", result010_cut, value);
                    }
                    else if ((char *)getItem(*dict, result011_cut) != NULL ) {
                        value =(char *)getItem(*dict, result011_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=011 %s of %s \n", result011_cut, value);
                    }
                    else if ((char *)getItem(*dict, result100_cut) != NULL ) {
                        value =(char *)getItem(*dict, result100_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=100 %s of %s \n", result100_cut, value);
                    }
                    else if ((char *)getItem(*dict, result101_cut) != NULL ) {
                        value =(char *)getItem(*dict, result101_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=101 %s of %s \n", result101_cut, value);
                    }
                    else if ((char *)getItem(*dict, result110_cut) != NULL ) {
                        value =(char *)getItem(*dict, result110_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=110 %s of %s \n", result110_cut, value);
                    }
                    else if ((char *)getItem(*dict, result111_cut) != NULL ) {
                        value =(char *)getItem(*dict, result111_cut) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=111 %s of %s \n", result111_cut, value);
                    }
                    else{
                        if ((char *)getItem(*dict, result000_cut2) != NULL ) {
                        value =(char *)getItem(*dict, result000_cut2) ;
                        temp_value = atof(value);
                        rapl_total_weight+=temp_value;
                        printf(" =%f",  atof(value));
                        //printf("total is %f\n",rapl_total_weight);
                        //printf("VALUE IS XXXXXXXXXXXXXXXXXX=000 %s of %s \n", result000_cut2, value);
                        }
                
                        else if ((char *)getItem(*dict, result001_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result001_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=001 %s of %s \n", result001_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result010_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result010_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=010 %s of %s \n", result010_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result011_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result011_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=011 %s of %s \n", result011_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result100_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result100_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=100 %s of %s \n", result100_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result101_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result101_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=101 %s of %s \n", result101_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result110_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result110_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=110 %s of %s \n", result110_cut2, value);
                        }
                        else if ((char *)getItem(*dict, result111_cut2) != NULL ) {
                            value =(char *)getItem(*dict, result111_cut2) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=111 %s of %s \n", result111_cut2, value);
                        }
                        else{
                            
                            if ((char *)getItem(*dict, result000_cut3) != NULL ) {
                            value =(char *)getItem(*dict, result000_cut3) ;
                            temp_value = atof(value);
                            rapl_total_weight+=temp_value;
                            printf(" =%f",  atof(value));
                            //printf("total is %f\n",rapl_total_weight);
                            //printf("VALUE IS XXXXXXXXXXXXXXXXXX=000 %s of %s \n", result000_cut3, value);
                            }
                
                            else if ((char *)getItem(*dict, result001_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result001_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=001 %s of %s \n", result001_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result010_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result010_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=010 %s of %s \n", result010_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result011_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result011_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=011 %s of %s \n", result011_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result100_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result100_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=100 %s of %s \n", result100_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result101_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result101_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=101 %s of %s \n", result101_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result110_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result110_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=110 %s of %s \n", result110_cut3, value);
                            }
                            else if ((char *)getItem(*dict, result111_cut3) != NULL ) {
                                value =(char *)getItem(*dict, result111_cut3) ;
                                temp_value = atof(value);
                                rapl_total_weight+=temp_value;
                                printf(" =%f",  atof(value));
                                //printf("total is %f\n",rapl_total_weight);
                                //printf("VALUE IS XXXXXXXXXXXXXXXXXX=111 %s of %s \n", result111_cut3, value);
                            }
                            else{
                                if (!strcmp(result.opcode,"syscall") ){
                                    fprintf(stderr,"We had a Syscall \n");
                                    } // see what to add for these
                                else{
                                    temp_value = 5;
                                    rapl_total_weight+=temp_value ;//bazoume 5 san mystery value
                                    printf(" =%f",  5.0);
                                    fprintf(fp3,"%s\n",result000);
                                    fprintf(stderr,"i cannot  find opcode %s or %s or %s or %s  \n",result000 ,result000_cut, result000_cut2, result000_cut3);}
                            }
                        }
                    }
                } 
            }
        
        }
    }
    printf("L@ %f\n", rapl_total_weight);



      
    

        fclose(fp);
        if (line)
        free(line);
    exit(EXIT_SUCCESS);
    
    
    return 0;
}

