#!/bin/bash
clang -o divider divider.c
rm divider_code.txt 2> /dev/null
rm divider_energy.txt 2> /dev/null
rm divider_log.txt 2> /dev/null
rm sums.txt 2> /dev/null
rm evaluation_real.txt 2> /dev/null
rm divider_lost.txt 2> /dev/null


touch divider_code.txt 
touch divider_energy.txt 
touch divider_log.txt 
touch sums.txt 
touch evaluation_real.txt
touch divider_lost.txt

./divider  ../cleaner_folder/trace_clean.txt divider_code.txt divider_energy.txt ../run_folder/rapl_original.txt ../remover_folder/updated_rapl_rest.txt ../remover_folder/updated_rapl_last.txt sums.txt ../cost_folder/cost.txt  evaluation_real.txt divider_lost.txt >>divider_log.txt