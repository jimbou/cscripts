//Auto einai to trito script
//pairnei san eisodo 4 arxeia
//1)to proto pou pargetai apo to divider.c (ekei pou bgainei o kodikas ton bb)
//2)to deutero pou pargetai apo to divider.c (ekei pou bgainei h energeia ton bb)
//3)to trito pou tha graftei o kodikas ton bb
//4)to tetarto pou tha graftei i energeia ton spasmenon bb
//5)to pempto pou grafetai katharismeni i energeia ton bb
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char * break_opcodes [] = { "%callq" , "%call", "retq" ,"ret","jump","jmp", "jne", "je" , "jg", "jle" ,"jge" , "jl", "calll" ,"retl" ,"callw" , "retw" ,"jz", "jnz" , "jns", "js", "ja", "jae", "jb","jbe","jc","jcxz","jecxz","jna","jnae","jnb",  "jnbe","jnc","jne","jng","jnge","jnle","jnl","jnle","jo", "jp", "jpe","jno","jnp","jnz","jpe","jpo"};

int main(int argc, char *argv[]) {

    //MAIN PART 1 : read the files 
    FILE * fp; //the file we gonna read code from
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE * fp1; //the file we gonna read energy from 
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    FILE * fp2; //the first file we gonna write code on 
    char * line2 = NULL;
    size_t len2 = 0;
    ssize_t read2;

    FILE * fp3; //the second file we gonna write energy on
    char * line3 = NULL;
    size_t len3 = 0;
    ssize_t read3;

    FILE * fp4; //the  file we gonna write clean energy on
    char * line4 = NULL;
    size_t len4 = 0;
    ssize_t read4;


    if (argc<5)
        {    //if an argument is not provided then error message and fail 
        fprintf(stderr,"You have not given the name of one or more argumets\n");
        fprintf(stderr,"Arguments should be in that order :\n 1)to proto pou pargetai apo to divider.c (ekei pou bgainei o kodikas ton bb)\n 2)to deutero pou pargetai apo to divider.c (ekei pou bgainei h energeia ton bb)\n 3)to trito pou tha graftei o kodikas ton bb\n 4)to tetarto pou tha graftei i energeia ton spasmenon bb\n 5)to tetarto pou tha graftei i clean energeia ton spasmenon bb\n");
        return 1;
        }
    fp  = fopen(argv[1], "r"); //to proto pou pargetai apo to divider.c (ekei pou bgainei o kodikas ton bb)
    fp1 = fopen(argv[2], "r");//to deutero pou pargetai apo to divider.c (ekei pou bgainei h energeia ton bb)
    fp2 = fopen(argv[3], "w"); //to trito gia output gia  code
    fp3 = fopen(argv[4], "w"); //to tetarto einai output gia energy
    fp4 = fopen(argv[5], "w"); //to tetarto einai output gia energy

    if (fp == NULL)
        {
        fprintf(stderr,"Could not open input code file\n");
        exit(EXIT_FAILURE);
        }
    if (fp1 == NULL)
        {
        fprintf(stderr,"Could not open input energy file\n");
        exit(EXIT_FAILURE);
        }
    if (fp2 == NULL)
        {
        fprintf(stderr,"Could not open file to output code\n");
        exit(EXIT_FAILURE);
        }
    if (fp3 == NULL)
        {
        fprintf(stderr,"Could not open file to output energy\n");
        exit(EXIT_FAILURE);
        }
    if (fp4 == NULL)
        {
        fprintf(stderr,"Could not open file to output clean energy\n");
        exit(EXIT_FAILURE);
        }




    char *code1=NULL, *code2=NULL;
    char *command1=NULL, *command2=NULL , *opcode =NULL;
    char *energy1=NULL , *energy2=NULL , *energy3=NULL ,*energy4=NULL , *energy5=NULL;
    int energy_counter1=0,energy_counter2=0 ,counter =0;
    float weight_total=0 , weight=0 , weight_temp=0, energy_total=0 , energy_temp=0;
    bool is_break = false;
    bool inside_A =false;
    bool just_printed =true;
    float  energy_lost=0;

     while ((read = getline(&line, &len, fp)) != -1)
     {
        if (strchr(line, '@') != NULL)  //periptosi rapl read
            {   
                if (strchr(line, 'L') != NULL) //teleutaio rapl read 
                    {energy_temp = (weight/ weight_total)*energy_total;
                    if ((counter ==0)&& (energy_temp/weight>1))
                        {
                            energy_lost += energy_temp;
                            energy_temp =-1*energy_temp;
                            
                        }
                    fprintf(fp3, "@ %d_%d: %f ,%f ,%f , ------%f\n",energy_counter2,counter, weight , weight_total , energy_total ,energy_temp);
                    fprintf(fp4, "@ %d_%d: %f %f \n",energy_counter2,counter,weight ,energy_temp);
                    break;
                    }

                read1 = getline(&line1, &len1, fp1); //diabazoume tin energeia
                if(read1 == -1)
                {
                    fprintf(stderr, "energy file has less lines than bbs\n");
                    return 1;
                }
                if (strchr(line, 'A') != NULL)
                {   if (just_printed ==false)
                    {   just_printed =true;
                        energy_temp = (weight/ weight_total)*energy_total;
                        if(energy_counter2 != 0)
                        {
                            if ((counter ==0)&& (energy_temp/weight>1))
                        {
                            energy_lost += energy_temp;
                            energy_temp =-1*energy_temp;
                            
                        }
                        fprintf(fp3, "@ %d_%d: %f ,%f ,%f , ------%f\n",energy_counter2,counter, weight , weight_total , energy_total ,energy_temp);
                        fprintf(fp4, "@ %d_%d: %f %f \n",energy_counter2,counter,weight ,energy_temp);
                        }
                    }
                    inside_A=true;
                    weight=0;
                    counter=0;
                    code1= strtok(line," "); 
                    code2= strtok(NULL,"\n");
                    energy_counter1=atoi(code2);// edo periexetai o aukson arithmos tou basic block apo arxeio kodika
                    energy1= strtok(line1," "); 
                    energy2= strtok(NULL," ");
                    energy3= strtok(NULL," ");
                    energy4= strtok(NULL," ");
                    energy5= strtok(NULL,"\n");
                    //printf("ρεαψηεδ ηερε4 %s , %s\n", energy2 , energy3);
                    energy_counter2=atoi(energy2); //  edo periexetai o aukson arithmos tou basic block apo arxeio energeion
                    weight_total=atof(energy3); //edo periexetai to baros tou basic block
                    energy_total=atof(energy5); //edo periexetai i energeia tou basic block

                    if(energy_counter1 != energy_counter2) //ama diaferoun oi 2 aukson arithmoi kati kaname lathos
                    {
                        fprintf(stderr, "The energy counters %d , %d are different \n", energy_counter1, energy_counter2);
                        return 1;
                    }
                    if (energy_counter2!=0)
                    {
                        fprintf(fp2, "@ %d_%d:\n", energy_counter2,counter); //ektipono gia to neo BB 
                        //fprintf(stderr,"Basic block number %d has energy %f\n", energy_counter1, weight_total );
                        if ((counter ==0)&& (energy_total/weight_total>1))
                        {
                            energy_lost += energy_total;
                            energy_total =-1*energy_total;
                            
                        }
                        fprintf(fp3, "@ %d_%d: %f ,%f ,%f , ------%f\n",energy_counter2,counter, weight_total , weight_total , energy_total ,energy_total);
                        fprintf(fp4, "@ %d_%d: %f %f \n",energy_counter2,counter,weight_total ,energy_total);
                    }
                    just_printed =true;
                    
                }
                else if ((strchr(line, 'B') != NULL) || (strchr(line, 'C') != NULL) )//periptosi rapl read 2 h rapl read 3
                {   if (just_printed ==false)
                    {   just_printed =true;
                        energy_temp = (weight/ weight_total)*energy_total;
                        if (energy_counter2!=0)
                        {
                                if ((counter ==0)&& (energy_temp/weight>1))
                            {
                                energy_lost += energy_temp;
                                energy_temp =-1*energy_temp;
                                
                            }
                            fprintf(fp3, "@ %d_%d: %f ,%f ,%f , ------%f\n",energy_counter2,counter, weight , weight_total , energy_total ,energy_temp);
                            fprintf(fp4, "@ %d_%d: %f %f \n",energy_counter2,counter,weight ,energy_temp);
                        }
                    }
                    inside_A=false;
                    weight=0;
                    counter=0;
                    code1= strtok(line," "); 
                    code2= strtok(NULL,"\n");
                    energy_counter1=atoi(code2);// edo periexetai o aukson arithmos tou basic block apo arxeio kodika
                    energy1= strtok(line1," "); 
                    energy2= strtok(NULL," ");
                    energy3= strtok(NULL," ");
                    energy4= strtok(NULL," ");
                    energy5= strtok(NULL,"\n");
                    //printf("ρεαψηεδ ηερε4 %s , %s\n", energy2 , energy3);
                    energy_counter2=atoi(energy2); //  edo periexetai o aukson arithmos tou basic block apo arxeio energeion
                    weight_total=atof(energy3); //edo periexetai to baros tou basic block
                    energy_total=atof(energy5); //edo periexetai i energeia tou basic block

                    if(energy_counter1 != energy_counter2) //ama diaferoun oi 2 aukson arithmoi kati kaname lathos
                    {
                        fprintf(stderr, "The energy counters %d , %d are different \n", energy_counter1, energy_counter2);
                        return 1;
                    }
                    if(energy_counter2!=0)
                    {
                        fprintf(fp2, "@ %d_%d:\n", energy_counter2,counter); //ektipono gia to neo BB 
                    }
                    //fprintf(stderr,"Basic block number %d has energy %f\n", energy_counter1, weight_total );
                
                }
                
                


            }
            else
            {   just_printed =true;
                if (energy_counter2 !=0)
                {
                fprintf(fp2,"%s",line); //ektipono tin grammi kodika
                }
                //opcode = strtok(line, " "); //periexetai to opcode tis entolis
               if (inside_A ==false)
                    {
                    opcode = strtok (line, " ");
                    command1= strtok(NULL,"="); 

                    command2= strtok(NULL,"\n");
                
                    if (command2 !=NULL)
                    {
                        weight_temp=atof(command2); //periexetai to weight tis entolis
                    }
                    else if (command1 !=NULL) 
                    {
                        weight_temp=atof(command1);
                    }
                    else 
                    {
                        printf("SOmething wrong with pointers in breker script\n");
                    }
                    weight =weight +weight_temp; //athroisma weight entolon tou spasmenou bb
                    is_break =false;
                    for(int i = 0; i < 46; ++i) //ama to opcode anoikei se break opcodes prepei na spasoume to bb
                    {
                        if(!strcmp(break_opcodes[i], opcode))
                        {
                            is_break=true;
                        }
                    }
                    just_printed=false;
                    if (is_break) //ama molis spasame to bb prepei na ektuposoume eenrgeia mexri tora kai na pame sto epomeno
                    {   energy_temp = (weight/ weight_total)*energy_total;
                        if (energy_counter2 !=0)
                        {
                        if ((counter ==0)&& (energy_temp/weight>1))
                        {
                            energy_lost += energy_temp;
                            energy_temp =-1*energy_temp;
                            
                        }
                        
                        fprintf(fp3, "@ %d_%d: %f ,%f ,%f , ------%f\n",energy_counter2,counter, weight , weight_total , energy_total ,energy_temp);
                        
                        fprintf(fp4, "@ %d_%d: %f %f \n",energy_counter2,counter,weight ,energy_temp);
                        }
                        weight =0;
                        counter++;
                        if (energy_counter2 !=0)
                        {
                        fprintf(fp2, "@ %d_%d:\n",energy_counter2,counter);
                        }
                        just_printed =true;
                    }
                    }
                 


            }
    }
    fprintf(fp4, "energy lost %f \n", energy_lost);
}