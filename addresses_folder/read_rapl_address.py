
import sys
import re
#pyhton script to give addresses of rapl functions
file_read = open(str(sys.argv[1]), "r")

function1 ="<rapl_A>"  #the first rapl function
function2 ="<rapl_B>"  #the second rapl function
function3 ="<rapl_C>"  #the second rapl function

start_function1=function1+":"
start_function2=function2+":"
start_function3=function3+":"

# reading file content line by line.
lines = file_read.readlines()
result1 = ""
result2 = ""
result3 = ""
break1 = False
break2 = False
break3 = False

inside_function1 = False
inside_function2 = False
inside_function3 = False

counter_function1 =0
counter_function2 =0
counter_function3 =0


# looping through each line in the file
for line in lines:
      
    # if line have the input string, get the index 
    # of that line and put the
    # line into newly created list 
    if(start_function1 in line ) :
        inside_function1= True
        counter_function1=-1
       
    
    if(start_function2 in line ) :
        inside_function2= True
        counter_function2=-1
    
    if(start_function3 in line ) :
        inside_function3= True
        counter_function3=-1

    if inside_function1 :
        counter_function1+=1
        if ("ret" in  line) or ("retq" in  line)  :
            inside_function1 =False
            result_A =line.split(':')[0]
    
    if inside_function2 :
        counter_function2+=1
        if ("ret" in  line) or ("retq" in  line)  :
            inside_function2 =False
            result_B =line.split(':')[0]

    if inside_function3 :
        counter_function3+=1
        if ("ret" in  line) or ("retq" in  line)  :
            inside_function3 =False
            result_C =line.split(':')[0]



        


    if (function1 in line) and (break1==False) :
        words = line.split()
        for idx, x in enumerate(words):
            if (x == "call" or x == "callq") and words[idx+2] == function1:
                result1 =words[idx+1]
                print("Result1 is ", result1 ," between words "  , x ,"  and ", words[idx+2],"\n")
                break1=True
        
    if (function2 in line) and (break2==False) :
        words = line.split()
        for idx, x in enumerate(words):
            if (x == "call" or x == "callq") and words[idx+2] == function2:
                result2 =words[idx+1]
                print("Result2 is ", result2 ," between words " , x ,"  and ", words[idx+2],"\n")
                break2=True

    if (function3 in line) and (break3==False) :
        words = line.split()
        for idx, x in enumerate(words):
            if (x == "call" or x == "callq") and words[idx+2] == function3:
                result3 =words[idx+1]
                print("Result3 is ", result3 ," between words " , x ,"  and ", words[idx+2],"\n")
                break3=True
        

 
# closing file after reading
file_read.close()



new_file_str = str(sys.argv[1][:-4]+ "_rapl_addresses.txt")
#to dimiourgei sto run directory
with open(new_file_str, 'w') as f:
    result_A.replace(" ", "")
    result_B.replace(" ", "")
    result_C.replace(" ", "")
    print("A"+" "+result1+result_A[1:] ,file=f)
    print("B"+" "+result2+result_B[1:] ,file=f)
    print("C"+" "+result3+result_C[1:] ,file=f)
