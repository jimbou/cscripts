#!/bin/bash
clang -o overhead_remover overhead_remover.c
rm updated_rapl_rest.txt 2> /dev/null
rm updated_rapl_last.txt 2> /dev/null
rm remover_log.txt 2> /dev/null

touch updated_rapl_rest.txt 
touch updated_rapl_last.txt 
touch remover_log.txt 

./overhead_remover ../run_folder/rapl_original.txt ../run_folder/rapl_rest.txt  ../run_folder/rapl_last.txt ../cost_folder/cost.txt updated_rapl_rest.txt updated_rapl_last.txt >>remover_log.txt