import sys
#pyhton script to give addresses of rapl functions
if (len(sys.argv) <3) :
    print("Did not provide enough arguments for python script find_missing.py")
file_read = open(str(sys.argv[1]), "r")
file_write = open(str(sys.argv[2]), "w")
sys.stdout = file_write

lines = file_read.readlines()
myset = set()
for line in lines :
    myset.add(line[:-7])

for item in myset:
    print(item)