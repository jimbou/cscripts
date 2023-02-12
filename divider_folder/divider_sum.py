#!/usr/bin/python

#this is the python script that find the enrgy cost of each rapl read 

import sys

n = len(sys.argv)
if(n<1):
    print("You have not given the 2 files as argument\n")
    print("1)file with dirty energy input\n")
    print("2)file with clean energy output\n")

dirty_file = open(str(sys.argv[1]), "r")

lines_dirty = dirty_file.readlines()
zeroed={}

total_weight =0
total_dirty_weight =0
total_dirty_energy=0
total_clean_energy=0
total_energy=0
for line in lines_dirty[1:]:
    line_temp = line.split()
    total_energy += float(line_temp[4])
    print(float(line_temp[4]))
print(total_energy)