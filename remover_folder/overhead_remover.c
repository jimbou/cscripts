//Auto einai to tetarto script
//pairnei san eisodo 5 arxeia
//0) to proto proto pou periexei tin original rapl read
//1)to proto pou periexei ta rest rapl reads
//2)to deutero pou periexei to finl rapl read
//3)to trito pou periexei to energy cost tou kathe rapl read
//4)to tetarto pou tha graftei to ananeomeno rest rapl read
//4)to pempto pou tha graftei to ananeomeno last rapl read
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int main(int argc, char *argv[]) {


    //MAIN PART 1 : read the files 

    FILE * fp0; //the file we gonna read original rapl read
    char * line0 = NULL;
    size_t len0 = 0;
    ssize_t read0;

    FILE * fp; //the file we gonna read rest rapl reads
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE * fp1; //the file we gonna last rapl read
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    FILE * fp2; //the first file we read rapl energy cost
    char * line2 = NULL;
    size_t len2 = 0;
    ssize_t read2;

    FILE * fp3; //the file we gonna write updated  rest rapl reads
    char * line3 = NULL;
    size_t len3 = 0;
    ssize_t read3;

    FILE * fp4; //the file we gonna write updated  last rapl read
    char * line4 = NULL;
    size_t len4 = 0;
    ssize_t read4;



    if (argc<6)
        {    //if an argument is not provided then error message and fail 
        fprintf(stderr,"You have not given the name of one ore more argumets\n");
        fprintf(stderr,"Arguments should be in that order :\n 0)to proto proto me to original rapl read 1)to proto me rest rapl reads\n 2)to deutero me last rapl read\n 3)to trito me rapl read cost\n 4)to tetarto pou tha graftei updated rest rapl reads\n 5)to pempro pou tha graftei updated last rapl read");
        return 1;
        }
    fp0  = fopen(argv[1], "r"); //1)to proto proto  me original rapl read
    fp  = fopen(argv[2], "r"); //1)to proto me rest rapl reads
    fp1 = fopen(argv[3], "r"); //2)to deutero me last rapl read
    fp2 = fopen(argv[4], "r"); //3)to trito me rapl read cost
    fp3 = fopen(argv[5], "w"); //to tetarto pou tha graftei updated rest rapl reads
    fp4 = fopen(argv[6], "w"); //to pempto pou tha graftei updated last rapl read


    if (fp0 == NULL)
        {
        fprintf(stderr,"Could not open original rapl read file\n");
        exit(EXIT_FAILURE);
        }
    if (fp == NULL)
        {
        fprintf(stderr,"Could not open rest rapl reads file\n");
        exit(EXIT_FAILURE);
        }
    if (fp1 == NULL)
        {
        fprintf(stderr,"Could not open last rapl read file\n");
        exit(EXIT_FAILURE);
        }
    if (fp2 == NULL)
        {
        fprintf(stderr,"Could not open rapl cost file\n");
        exit(EXIT_FAILURE);
        }
    if (fp3 == NULL)
        {
        fprintf(stderr,"Could not open file to output updated rest rapl read\n");
        exit(EXIT_FAILURE);
        }
    if (fp4 == NULL)
        {
        fprintf(stderr,"Could not open file to output updated last rapl read\n");
        exit(EXIT_FAILURE);
        }



    
    long double cost =0 ,clean=0;
    char *energy1 =NULL;
    char *energy_tmp =NULL,*original_temp =NULL , *last_temp=NULL ;
    int num_prv_reads =1;
    long double current_read =0, prev_read =0 ,last =0;
    long double result=0;

    if((read0 = getline(&line0, &len0, fp0)) != -1)
    {
        original_temp= strtok(line0, "\n");
        prev_read = atof(original_temp); //read the individual rapl cost
    }

    if((read1 = getline(&line1, &len1, fp1)) != -1)
    {
        last_temp= strtok(line1, "\n");
        last = atof(last_temp); //read the individual rapl cost
    }
    
    while((read2 = getline(&line2, &len2, fp2)) != -1)
    {
        last_temp=strtok(line2, "\n");
        cost =clean;
        clean = atof(last_temp); //read the individual rapl cost
        
    }
    //fprintf(stderr,"cost = %LF\n" ,cost);
    //fprintf(stderr,"clean = %LF\n" ,clean);

  
    while ((read = getline(&line, &len, fp)) != -1)
    {
        energy_tmp= strtok(line, "\n");
        current_read= atof(energy_tmp);
        //fprintf(stderr,"%LF\n" ,current_read);
        if (prev_read != current_read) //rapl read energy read has changed
        {
            result = current_read - (num_prv_reads*cost);
            num_prv_reads++;
            prev_read =current_read;
            fprintf(fp3,"%LF\n",result);
        }
        else  //rapl read energy has stayed the same
        {
            num_prv_reads++;
            fprintf(fp3,"%LF\n",result);

        }

    }
    if(prev_read !=last )
    {
        result = last - (num_prv_reads*cost);
        num_prv_reads++;
        fprintf(fp4,"%LF\n",result);
    }
    else
    {
        fprintf(fp4,"%LF",result);
    }
}
