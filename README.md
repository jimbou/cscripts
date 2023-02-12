This repo takes needs the following to run and provide us with the energy of the Basic Blocks of the executable:

1) The name of the executable
2) The dis-assembled code of the executable
3) The trace of the executable
4) 3 Rapl read files :
  a) the original from a read before the executable is run
  b) the rapl reads caused by the pass in the executable
  c) the last from a read after the executable is run
5) 2 rapl reads one before and one after the unpassed executable
6)the opcodes csv with opcode weights from intel manuals

and gives us the following as a result:

1) a file with all the basic blocks each with a unique id
2) a file with the energy of each basic block with the unique id corresponding to the code from the previous file

to run put the necessary files in the run_folder and give the corresponding name to the run_addresses.sh
then run ./total.sh

total.sh -> the full script to run the repo : calls all the other scripts from each individual folder

run_addresses.sh -> gives us the addresses of the rapl read functions (the calls performed)

run_opcode.sh -> from the opcodes.csv it gives the opcodes.txt turning the opcodes in the desired format

run_cost.sh -> gives the cost of each rapl read call

run_remover.sh -> removes the overhead cost of the rapl read calls from the energies

run_cleaner.sh -> get the weight of each command

run_divider.sh -> get the energy of each basic object based on the weights

run_breaker.sh -> split basic objects into basic blocks and correspond them with energy
