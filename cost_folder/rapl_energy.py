#!/usr/bin/python

#this is the python script that find the enrgy cost of each rapl read 

import sys
 
# total arguments
n = len(sys.argv)
if(n<5):
    print("You have not given the 3 files as argument\n")
    print("1)file of first rapl read\n")
    print("2)file of rest rapl reads\n")
    print("3)file of last rapl read\n")
    print("4)file with first and last rapl read of executable that hasnt passed from pass\n")
    print("5)file where rapl read cost will be written\n")

for i in range(1, n):
    print(sys.argv[i], end = " ")



with open(sys.argv[1]) as f1:
    for line1 in f1:
        pass
    last_line1 = float(line1)
    

rest_file = open(str(sys.argv[2]), "r")
lines_rest = rest_file.readlines()
counter = len(lines_rest)
last_line2= float(lines_rest[0][:-1])



with open(sys.argv[3]) as f3:
    for line3 in f3:
        pass
    last_line3 = float(line3)

f4 = open(sys.argv[4])
content = f4.readlines()
first_clean = float(content[0])
last_clean = float(content[1])

clean = last_clean - first_clean #kathari energeia tou ektelesimou
dirty = last_line3 -last_line2 #energeia ektelesimou mazi me rapl reads
overhead =dirty - clean #ekstra kostos rapl reads sunoliko
cost = overhead /counter #kostos kathe rapl read



print("clean is ", clean , "\n")
print("dirty is ", dirty , "\n")
print("overhead is ", overhead , "\n")
print("cost is ", cost , "\n")
print("counter is ", counter , "\n")

with open(sys.argv[5], 'w') as f5:
    f5.write(str(cost)+"\n")
    f5.write(str(clean)+"\n")