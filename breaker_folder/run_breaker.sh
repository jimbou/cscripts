#!/bin/bash
clang -o breaker breaker.c
rm breaker_code.txt 2> /dev/null
rm breaker_energy.txt 2> /dev/null
rm breaker_clean_energy.txt 2> /dev/null
rm breaker_final_energy.txt 2> /dev/null
rm breaker_log.txt 2> /dev/null
rm evaluation.txt 2> /dev/null

touch breaker_code.txt 
touch breaker_energy.txt
touch breaker_clean_energy.txt  
touch breaker_log.txt 
touch breaker_final_energy.txt 
touch evaluation.txt

./breaker  ../divider_folder/divider_code.txt ../divider_folder/divider_energy.txt breaker_code.txt breaker_energy.txt breaker_clean_energy.txt  2>breaker_log.txt
python3 breaker.py breaker_clean_energy.txt breaker_final_energy.txt  ../divider_folder/divider_lost.txt #evaluation.txt
mv ../divider_folder/evaluation_real.txt .