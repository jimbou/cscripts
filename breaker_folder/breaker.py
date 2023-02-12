#!/usr/bin/python

#this is the python script that find the enrgy cost of each rapl read 

import sys

n = len(sys.argv)
if(n<2):
    print("You have not given the 2 files as argument\n")
    print("1)file with dirty energy input\n")
    print("2)file with clean energy output\n")

dirty_file = open(str(sys.argv[1]), "r")
clean_file= open(str(sys.argv[2]), "w")
lost_file= open(str(sys.argv[3]), "r")

lines_dirty = dirty_file.readlines()
lines_lost = lost_file.readlines()
zeroed={}


lost_prev = float(((lines_lost[0]).split())[0])

total_weight =0
total_dirty_weight = 0
total_dirty_energy=0
total_clean_energy=0
total_energy=0
for line in lines_dirty[:-1]:
    data = line.split()
    total_weight+=float(data[2])
    temp =float(data[3])
    
    if (temp>=0):
        total_clean_energy+=temp
    else:
        total_dirty_weight+= float(data[2])
        total_dirty_energy-= temp
        zeroed[data[1]] = float(data[2])

#print(total_clean_energy,total_dirty_energy)
total_dirty_energy += lost_prev
print("TOTALLLLLLLLLLLLLLLLL" ,total_dirty_energy + total_clean_energy)
overhead = ((total_clean_energy+total_dirty_energy)/total_clean_energy)*(total_weight -total_dirty_weight)/total_weight
remaining =  ((total_clean_energy+total_dirty_energy)/total_clean_energy)*(total_dirty_weight)/total_weight
remaining=remaining*total_clean_energy
#print((overhead-1)*total_clean_energy)
#print (remaining)
#print(((overhead+remaining)-1)*total_clean_energy)
sum=0
sum1=0
with open(sys.argv[2], 'w') as f5:
    #f5.write(str(cost)+"\n")
    for line in lines_dirty[:-1]:
        data = line.split()
        temp =float(data[3])
        if (temp>=0):
            temp1 =float(data[3])*overhead
            sum+=temp1
            f5.write(str(data[0])+" "+str(data[1])+" "+str(temp1)+"\n")
        else :
            temp = zeroed[data[1]]
            temp= (temp/total_dirty_weight)*remaining
            sum1+=temp
            f5.write(str(data[0])+" "+str(data[1])+" "+str(temp)+"\n")
        

#print("sum: "+str(sum))
#print("sum1: "+str(sum1))
#print("total: "+ str(sum+sum1))
#with open(sys.argv[3], 'w') as f4:
#   f4.write("total_real: "+str(total_clean_energy+total_dirty_energy)+"\n")


   




