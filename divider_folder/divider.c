//Auto einai to deutero script
//pairnei san eisodo 6 arxeia
//1)auto pou pargetai apo to cleaner.c (ekei pou bgainei to stdout tou cleaner.c)
//2)output for BBs code -ekei tha graftei o kodikas ton bb
//3)output for bb energy- ekei tha graftei i energeia ton bbs
//4)input me energeia arxikou rapl read
//5)input with the rest rapl energies
//6)input with the last rapl read energy
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct node {
    long double val;
    struct node * next;
} node_t;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%LF\n", current->val);
        current = current->next;
    }
}

int list_len(node_t * head) {
    node_t * current = head;
    int len =0;
    while (current != NULL) {
       len++;
        current = current->next;
    }
    return len;
}
void push_last(node_t * head, long double val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void push_first(node_t ** head, long double val) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

long double pop(node_t ** head) {
    long double retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

long double remove_last(node_t * head) {
    long double retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}

long double remove_by_index(node_t ** head, int n) {
    int i = 0;
    long double retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return -1;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

int main(int argc, char *argv[]) {


    //MAIN PART 1 : read the file and copy 
    FILE * fp; //the file we gonna read from
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE * fp1; //the first file we gonna write on 
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    FILE * fp2; //the second file we gonna write on
    char * line2 = NULL;
    size_t len2 = 0;
    ssize_t read2;

    FILE * fp3; //the input file with first rapl read energy
    char * line3 = NULL;
    size_t len3 = 0;
    ssize_t read3;

    FILE * fp4; //the input file with rest rapl read energies
    char * line4 = NULL;
    size_t len4 = 0;
    ssize_t read4;

    FILE * fp5; //the input file with last rapl read energy
    char * line5 = NULL;
    size_t len5 = 0;
    ssize_t read5;

    FILE * fp6; //the output file for the sums
    char * line6 = NULL;
    size_t len6 = 0;
    ssize_t read6;

    FILE * fp7; //the input cost file
    char * line7 = NULL;
    size_t len7 = 0;
    ssize_t read7;

    FILE * fp8; //the input cost file
    char * line8 = NULL;
    size_t len8 = 0;
    ssize_t read8;


    FILE * fp9; //the input cost file
    char * line9 = NULL;
    size_t len9 = 0;
    ssize_t read9;

    long double original_read,final_read, previous_read , current_read , current_energy , current_weight, current_total_weight , current_total_energy , sum_of_weight =0 , sum_of_energy =0 ,total_streak=0,zero_streak=0 ,clean =0 ,cost=0;
    const char s[2] = "\n";
    char* token;

    char* command_weight =NULL;
    char* temp =NULL;
    char* temp1 =NULL;
    char* temp2 =NULL;


    if (argc<10)
        {    //if an argument is not provided then error message and fail 
        fprintf(stderr,"You have not given the name of one ore more argumets\n");
        fprintf(stderr,"Arguments should be in that order :\n 1)cleaner script output file\n 2)output for BBs code\n 3)output for bb energy\n 4)input me energeia arxikou rapl read\n 5)input with the rest rapl energies\n 6) input me last rapl read energy\n 7) output gia sums\n 8) the input cost file\n 9) the output for expected sum \n 9)lost energy file to write\n ");
        return 1;
        }
    fp  = fopen(argv[1], "r"); //to proto argument einai to onoma tou arxeiou me to apotelsma tou cleaner script
    fp1 = fopen(argv[2], "w");//to  deutero to output gia bbs code
    fp2 = fopen(argv[3], "w"); //to trito gia output gia bbs energy
    fp3 = fopen(argv[4], "r"); //to tetarto einai input me enrgeia tou first rapl read
    fp4 = fopen(argv[5], "r"); //to pempto einai input me enrgeia apo rest of rapl reads
    fp5 = fopen(argv[6], "r"); //to pempto einai input me enrgeia apo last of rapl read
    fp6 = fopen(argv[7], "w"); //to output gia sums
    fp7 = fopen(argv[8], "r"); //to input  gia costs
    fp8 = fopen(argv[9], "w"); //to output gia expected energy sum
    fp9 = fopen(argv[10], "w"); //to output gia lost energy

    if (fp == NULL)
        {
        fprintf(stderr,"Could not open file with output of cleaner script\n");
        exit(EXIT_FAILURE);
        }
    if (fp1 == NULL)
        {
        fprintf(stderr,"Could not open file to output BBs code\n");
        exit(EXIT_FAILURE);
        }
    if (fp2 == NULL)
        {
        fprintf(stderr,"Could not open file to output BBs energy\n");
        exit(EXIT_FAILURE);
        }
    if (fp3 == NULL)
        {
        fprintf(stderr,"Could not open file for input with the first rapl read\n");
        exit(EXIT_FAILURE);
        }
    if (fp4 == NULL)
        {
        fprintf(stderr,"Could not open file for input with the rest rapl reads\n");
        exit(EXIT_FAILURE);
        }
    if (fp5 == NULL)
        {
        fprintf(stderr,"Could not open file for input with the last rapl read\n");
        exit(EXIT_FAILURE);
        }
    if (fp6 == NULL)
        {
        fprintf(stderr,"Could not open file for output of sums\n");
        exit(EXIT_FAILURE);
        }
    if (fp7 == NULL)
        {
        fprintf(stderr,"Could not open file for input of cost\n");
        exit(EXIT_FAILURE);
        }

    if (fp8 == NULL)
        {
        fprintf(stderr,"Could not open file for input of cost\n");
        exit(EXIT_FAILURE);
        }
    if (fp9 == NULL)
        {
        fprintf(stderr,"Could not open file for write lost energy\n");
        exit(EXIT_FAILURE);
        }

    read3 = getline(&line3, &len3, fp3);
    read5 = getline(&line5, &len5, fp5);
    final_read = atof(line5);;
    original_read=atof(line3);
    previous_read=original_read;

//ORISMOS LISTAS

node_t * head = NULL;
head = (node_t *) malloc(sizeof(node_t));
if (head == NULL) {
    return 1;
}


head->val = original_read;
head->next = NULL;

node_t * weight = NULL;
weight = (node_t *) malloc(sizeof(node_t));
if (weight == NULL) {
    return 1;
}


weight->val = 0;
weight->next = NULL;


node_t * total_weight = NULL;
total_weight = (node_t *) malloc(sizeof(node_t));
if (total_weight == NULL) {
    return 1;
}
total_weight->val = 0;
total_weight->next = NULL;

node_t * total_energy = NULL;
total_energy = (node_t *) malloc(sizeof(node_t));
if (total_energy == NULL) {
    return 1;
}
total_energy->val = 0;
total_energy->next = NULL;
bool first_time=true;
char *last_temp=NULL ;

    while((read7 = getline(&line7, &len7, fp7)) != -1)
    {
        last_temp=strtok(line7, "\n");
        cost =clean;
        clean = atof(last_temp); //read the individual rapl cost
        
    }
    fprintf(fp6,"cost = %LF\n" ,cost);
    fprintf(fp6,"clean = %LF\n" ,clean);


    while ((read4 = getline(&line4, &len4, fp4)) != -1) 
        {
        total_streak+=1;
        token = strtok(line4, s);  //here changes need to be made
        current_read= atof(token);
        current_energy = current_read-previous_read; 
        if (current_energy<=0)
            {
            zero_streak+=1;
            current_energy=0;
           push_last(head,current_energy); 
           //printf ("%LF\n", current_energy);
            }
        else
            {
            //printf ("%LF\n", current_energy);
            if (!first_time)
            {
            sum_of_energy=sum_of_energy +current_energy;
            }
            zero_streak=0;
            push_last(head,current_energy);
            previous_read=current_read; 
            first_time=false;
            }
        }
    
    current_energy = pop(&head); 
    
    if ((final_read-previous_read)>0)
        {
            zero_streak=0;
        sum_of_energy=sum_of_energy +(final_read-previous_read);
        push_last(head,final_read-previous_read);

        }
    else
        {
        zero_streak+=1;
        push_last(head,0); 
        }
    printf("LIST OF RAPL ENERGIES IS :\n");
    print_list(head);
    fprintf(fp6,"%LF\n",sum_of_energy);
    
    fprintf(fp6,"total streak:  %LF\n",total_streak);
    fprintf(fp6,"zero streak: %LF\n",zero_streak);
    
    
    //edo i lista head periexei oles tis energeis anamesa se rapl reads
    bool first = true;
    int counter = 0; //autos o counter tha antistoixizei kathe bb me tin eenrgeia tou
    while ((read = getline(&line, &len, fp)) != -1) 
        { 
        if (strchr(line, '@') != NULL)
        {
        temp1= strtok(line,"@"); 
        temp2= strtok(NULL,"\n");
        current_weight=atof(temp2);
        push_last(weight,current_weight);
        if(!first){
        sum_of_weight = sum_of_weight+ current_weight;
        }
        first=false;

        }
        }
        current_weight = pop(&weight);
        printf("LIST OF WEIGHT IS :\n");
        print_list(weight);
        fprintf(fp6,"%LF\n",sum_of_weight);

    //edo i lasta weight periexei ola ta bari ton bb
    node_t * list_important_weight = weight->next ;
    
    long double important_sum =0 ,rest_sum=0, counter_important = total_streak -zero_streak;
     while ((list_important_weight != NULL))
    {   
        if(counter_important>0)
        {
            important_sum = important_sum +list_important_weight->val;
            counter_important-=1;
            list_important_weight =list_important_weight->next;
        }
        else 
        {
            rest_sum =rest_sum + list_important_weight->val;
            list_important_weight =list_important_weight->next;

        }
    }
    fprintf(fp6,"important weight %LF \n",important_sum);
    fprintf(fp6,"sum of  weight %LF \n",sum_of_weight);
    node_t * list_head = head ;
    node_t * list_weight = weight ;
    long double temp_head ,temp_weight ,total_temp_weight =0 ;
    

    while ((list_head != NULL) && (list_weight != NULL))
    {
        temp_head = list_head->val;
        temp_weight = list_weight->val;
        total_temp_weight = total_temp_weight +temp_weight;
        if (temp_head != 0)
        {   push_last(total_energy,temp_head);
            //printf("puting weight %LF \n", total_temp_weight);
            push_last(total_weight,total_temp_weight );
            total_temp_weight=0;
        }
        list_head= list_head->next; 
        list_weight =list_weight->next;
        

    }
    printf("LIST OF TOTAL WEIGHT IS :\n");
    long double not_important = pop(&total_weight);
    print_list(total_weight);

     //Edo i lista total_weight exei simplirothei : auti perixei ta total weigths gia polla bb pou apoteloun ena rapl read interval

    printf("LIST OF TOTAL ENERGY IS :\n");
    not_important = pop(&total_energy);
    print_list(total_energy);
    
    //Edo i lista total_energy exei simplirothei :auti periexei tin energeia pou antistoixei se ena energy interval
    fprintf(fp6,"sum_of_weight = %LF \n", sum_of_weight);
    fprintf(fp6,"important_sum = %LF \n", important_sum);
    fprintf(fp6,"rest_sum = %LF \n", rest_sum);
   
    long double overhead= (clean * ((important_sum)/sum_of_weight))/sum_of_energy;
    fprintf(fp6,"overhead = %LF \n", overhead);
    long double total_amount=0;
    node_t * list_total_energy = total_energy->next;
    while ((list_total_energy != NULL))
    {
        temp_head = list_total_energy->val;
        temp_head=temp_head*overhead;
        total_amount +=temp_head;
        list_total_energy->val = temp_head;
        list_total_energy =list_total_energy->next;
    } 
    push_last(total_energy,clean-total_amount); //prosteto tin energeia pou perisseuei sto telos
    push_last(total_weight,rest_sum); //prostheto ton baros ton perisseuomenon sto telos
    long double temp_total =0;
    node_t * temp_help = total_energy->next;
    while ((temp_help != NULL))
    {
        temp_total = temp_total + temp_help->val;
        temp_help =temp_help->next;
    }
    long double temp_total_w2 =0;
    node_t * temp_help1 = total_weight;
    while ((temp_help1 != NULL))
    {
        temp_total_w2 = temp_total_w2 + temp_help1->val;
        temp_help1 =temp_help1->next;
    }
    long double temp_weight1 =0;
    node_t * temp_help2 = weight;
    while ((temp_help2 != NULL))
    {
        temp_weight1 = temp_weight1 + temp_help2->val;
        temp_help2 =temp_help2->next;
    }
     //fprintf(fp6,"list of total weight len = %d \n", list_len(total_weight));
     //fprintf(fp6,"list of total energy len = %d \n", list_len(total_energy));
    //fprintf(fp6,"total streak = %LF \n", total_streak);
     //fprintf(fp6,"zeros streak = %LF \n", zero_streak);
    printf("clean is %LF \n",clean);
    printf("total is %LF \n",temp_total);
     printf("total weight sum is %LF \n",temp_total_w2);
      printf("weight is %LF \n",temp_weight1);


    fprintf(fp8,"expected amount = %LF \n", clean);
    //fprintf(fp8,"rest amount = %LF \n",clean - total_amount);
    //fprintf(fp8,"sure rest amount = %LF \n",total_amount*(sum_of_weight-important_sum)/important_sum);
    printf("UPDATED LIST OF TOTAL ENERGY IS :\n");
    print_list(total_energy);

    printf("UPDATED LIST OF TOTAL WEIGHT IS :\n");
    print_list(total_weight);

    current_total_weight = pop(&total_weight);
    current_total_energy = pop(&total_energy);
    

    //fprintf(fp2, "%LF %LF \n", current_total_weight, current_total_energy);
    long double result;
    
    char type_of_rapl_read= 'B'; 
    char prev_type_of_rapl_read= 'B'; 
    fp  = fopen(argv[1], "r");
    fprintf(fp1,"B@ %d\n",counter);

    printf("UPDATED LIST OF TOTAL ENERGY IS :\n");
    print_list(total_energy);

    printf("UPDATED LIST OF TOTAL WEIGHT IS :\n");
    print_list(total_weight);
    long double temporary_sum=0 ,temporary_sum1=0;
    bool first_time1=true;
    long double weightsum =0, tmpsum1=0,tmpsum2=0 ,tmpsum3=0,tmpsum4=0;

    read = getline(&line, &len, fp); //gia na fugei i keni grammi pano pano 
     while ((read = getline(&line, &len, fp)) != -1)  
        {
            
        //opote blep rapl read ama mpika se nao inteval annaneono ta current_total_energy kai current_total_weight
        //allios xrhsimopoio auta tou interval pou eimai tora kai me basi to baros tou torinou bb xorizo tin energeia tou interval
        //pou eimai tora gia na paei kapoia sto bb pou eimai tora 
            if (strchr(line, 'A') != NULL)  
            {
                type_of_rapl_read ='A';
            }
            else if (strchr(line, 'B') != NULL)  
            {
                type_of_rapl_read ='B';
            }
            else if (strchr(line, 'C') != NULL) 
            {
                type_of_rapl_read ='C';
            }
            else
            {
                type_of_rapl_read = 'L';
            }

            
            
            if((strchr(line, '@') != NULL))
            {   
                
                
                current_weight = pop(&weight);
                weightsum+=current_weight;
                current_energy = pop(&head);
                if (current_total_weight != 0)
                    {
                    result = (current_weight / current_total_weight ) * current_total_energy; 
                    if (first_time1){ 
                        printf("I AM HEREEEEEEEEEEEEEEEEEEEEEE %LF\n", result);
                        tmpsum4=result;}
                    temporary_sum1+=current_weight / current_total_weight;
                    if(!first_time1){
                    temporary_sum+=result;
                    }
                    first_time1=false;
                    }
                else 
                    {
                    result =0;
                    }
                fprintf(fp2,"%c@ %d %LF %LF %LF \n",prev_type_of_rapl_read, counter, current_weight , current_total_weight,  result);
                counter++;
                prev_type_of_rapl_read = type_of_rapl_read;
                if (strchr(line, 'L') == NULL) {//dn einai to teleutaio rapl read  
                fprintf(fp1,"%c@ %d\n",type_of_rapl_read,counter);}
                else {fprintf(fp1,"L@ %d\n",counter);}

                if (current_energy != 0)
                {
                tmpsum3 += current_total_energy;
                current_total_energy = pop(&total_energy);
                if (current_total_energy == -1){
                    current_total_energy =0;
                }
                printf("\ntotal %LF vs sum %LF   \n", current_total_weight, weightsum);
                printf ("close to 1 is %LF\n", temporary_sum1);
                temporary_sum1=0;
                tmpsum1+=current_total_weight;
                tmpsum2+=weightsum;
                weightsum =0;
                current_total_weight = pop(&total_weight);
                if (current_total_weight == -1){
                    current_total_weight =0;
                }
            }
            
            


            
            

            }
            else if (strchr(line, '+') != NULL)
            {
                ;
            }
            else 
            {
                //temp= strtok(line,"-");  //the command is splitted into the actual command
                //command_weight =strtok(NULL,"\n"); //and its weight
                fprintf(fp1,"%s",line);

            }
        
        }
     printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %LF \n",temporary_sum)   ;
     fprintf(fp9,"%LF",clean-temporary_sum );
     printf("length of weight is %d \n", list_len(weight));
     printf("length of total_weight is %d \n", list_len(total_weight));
     printf("length of total_energy is %d \n", list_len(total_energy));
     printf("\ntotal sum %LF vs sum sum %LF   \n", tmpsum1, tmpsum2);
     printf("\ntotal energy sum %LF vs first energy  sum %LF  vs rest energy sum %LF  \n", tmpsum3, tmpsum4, tmpsum3-tmpsum4);

    
}




