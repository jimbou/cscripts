#!/bin/bash
rm cost.txt 2> /dev/null
touch cost.txt

python3 rapl_energy.py ../run_folder/rapl_original.txt ../run_folder/rapl_rest.txt  ../run_folder/rapl_last.txt  ../run_folder/first_last_rapl.txt cost.txt