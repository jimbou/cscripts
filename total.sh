#!/bin/bash
cd addresses_folder 
./run_addresses.sh $1
echo "ran addresses"
cd ..
cd cost_folder
./run_cost.sh
echo "ran cost"
cd ..
cd remover_folder
./run_remover.sh
echo "ran remover"
cd ..
cd cleaner_folder
./run_cleaner.sh $1
echo "ran cleaner"
cd ..
cd divider_folder
./run_divider.sh
echo "ran divider"
cd ..
cd breaker_folder
./run_breaker.sh
echo "ran breaker"
cd ..