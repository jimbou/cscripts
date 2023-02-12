#!/usr/bin/python

import json
import sys
import re
import pandas as pd


regs =['%eax' , "%ebx" ,"%ecx", "%edx", "%cs", "%ds", "%es", "%fs", "%gs", "%ss","%esi", "%edi" , "%ebp", "%eip" ,"%esp", "%ax", "%bx", "%cx" , "%dx" ,"%ah" ,"%al" ,"%bh" ,"%bl" , "%ch" ,"%dh" ,"%dl" ,"%rax", "%rcx" ,"%rdx" ,"%rbx" ,"%rsp" ,"%rbp" ,"%rsi" ,"%rdi" ,"%sp" ,"%bp" ,"%si" ,"%di" ,"%spl" ,"%bpl" ,"%sil" ,"%dil" , "%ss" ,"%cs" ,"%ds" ,"%es" ,"%fs" ,"%gs" ,"%eflags" ,"%eip"  ]

df = pd.read_csv('opcodes_6.csv',dtype=str)
df =df.drop(df.columns[5], axis=1)
df.dropna(subset=['name'], inplace=True)
df =df.reset_index(drop=True)
print(df)
df =df.fillna("0")

df1 = pd.DataFrame(columns = ['name', 'weight'])

for ind in df.index:
    print(df['name'][ind])
    s = df['name'][ind]+"_"+df['op1'][ind]+"_"+df['op2'][ind]+"_"+df['op3'][ind]
    
    new_row = pd.DataFrame({'name' : s, 'weight' : df['weight'][ind]}, index=[0])
    df1 = pd.concat([new_row,df1.loc[:]]).reset_index(drop=True)

    
print(df1)
arr =df1.to_numpy()


wtfile = open('opcodes.txt', 'w+')
for ind in df1.index:
    wtfile.write(df1['name'][ind]+" "+df1['weight'][ind]+"\n")
wtfile.close()

"""
with open(str(sys.argv[1])) as f:
    my_dict = json.load(f)
opcodes =[]
tmp =0
weights = {}
for key, value in my_dict.items():
    weights[key] =0
    for item in value :
        
        #x = re.split('/\s{1,}|,|\t{1,}/g', item)
        x = re.split(r"\s+|,", item)
        opcodes.clear()
        tmp =min(4,len(x))
        for i in range(tmp):
            opcodes.append(x[i])
        if (tmp == 4):
            arg1 = opcodes[1]
            arg2 = opcodes[2]
            arg3 = opcodes[3]
        elif (tmp == 3):
            arg1 = opcodes[1]
            arg2 = opcodes[2]
            arg3 = ""
        elif (tmp == 2):
            arg1 = opcodes[1]
            arg2 = ""
            arg3 = ""
        else:
            arg1 = ""
            arg2 = ""
            arg3 = ""


        #print (opcodes,"\n")
        #print (x[0]," ", arg1," ",arg2," ",arg3," ","\n")

        if arg1 in regs:
            arg1 ="r"
        elif ('(' in arg1 ) and (')' in arg1 ):
            arg1 ="m"
        elif arg1.startswith('<') and arg1.endswith('>') :
            arg1 ="m"
        elif arg1.startswith('%'):
            arg1 ="m"
        elif arg1.startswith("$0x"):
            arg1 ="I"
        elif arg1 == "%cl":
            arg1 ="cl"
        else :
            arg1 =""

        if arg2 in regs:
            arg2 ="r"
        elif ('(' in arg2 ) and (')' in arg2 ):
            arg2 ="m"
        elif arg2.startswith('<') and arg2.endswith('>') :
            arg2 ="m"
        elif arg2.startswith('%'):
            arg2 ="m"
        elif arg2.startswith("$0x"):
            arg2 ="I"
        elif arg2 == "%cl":
            arg2 ="cl"
        else :
            arg2 =""
        
        if arg3 in regs:
            arg3 ="r"
        elif ('(' in arg3 ) and (')' in arg3 ):
            arg3 ="m"
        elif arg3.startswith('%'):
            arg3 ="m"
        elif arg2.startswith('<') and arg3.endswith('>') :
            arg2 ="m"
        elif arg3.startswith("$0x"):
            arg3 ="I"
        elif arg3 == "%cl":
            arg3 ="cl"
        else :
            arg3 =""

        print (opcodes,"\n")
        print (x[0]," ", arg1," ",arg2," ",arg3," ","\n")

        
        df_temp = df.loc[df['name'] == x[0]]
        if df_temp.empty :
            df_temp = df.loc[df['name'] == x[0][:-1]]
        if df_temp.empty :
            df_temp = df.loc[df['name'] == x[0][:-2]]
        if df_temp.empty :
            df_temp = df.loc[df['name'] == x[0][:-3]]
        if df_temp.empty :
            df_temp = df.loc[df['name'] == x[0][:-4]]
        if df_temp.empty :
            print("Could not find opcode  : ", x[0] ,"\n")

        res_weight =3 
        
        if not df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op2'] == arg2) & (df_temp['op3'] == arg3)].empty :
            res_weight = df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op2'] == arg2) & (df_temp['op3'] == arg3)].iloc[0]['weight']
        elif not df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op2'] == arg2) ].empty :
            res_weight = df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op2'] == arg2) ].iloc[0]['weight']
        elif not df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op3'] == arg3) ].empty :
            res_weight = df_temp.loc[(df_temp['op1'] == arg1) & (df_temp['op3'] == arg3) ].iloc[0]['weight']
        elif not df_temp.loc[(df_temp['op3'] == arg3) & (df_temp['op2'] == arg2) ].empty :
            res_weight = df_temp.loc[(df_temp['op3'] == arg3) & (df_temp['op2'] == arg2) ].iloc[0]['weight']
        elif not df_temp.loc[df_temp['op1'] == arg1  ].empty :
            res_weight = df_temp.loc[df_temp['op1'] == arg1  ].iloc[0]['weight']
        elif not df_temp.loc[df_temp['op2'] == arg2  ].empty :
            res_weight = df_temp.loc[df_temp['op2'] == arg2  ].iloc[0]['weight']
        elif not df_temp.loc[df_temp['op3'] == arg3  ].empty :
            res_weight = df_temp.loc[df_temp['op3'] == arg3  ].iloc[0]['weight']
        elif not df_temp.empty :
            res_weight = df_temp.iloc[0]['weight']
        else :
            print (print("Could not find opcode  : ", x[0] ," ", arg1," ",arg2," ",arg3," ", "\n"))
        
        print ("the result weight is ", res_weight , "\n")
        weights[key] += float(res_weight)
        



     


        print(df_temp)
        print ("\n")
        #print(opcodes ,"\n")  



#print(df.to_string()) 

""" 