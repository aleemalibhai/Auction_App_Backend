#!/bin/sh

# For text colouring purpose
BLUE='\033[1;34m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Uncomment line 4 - 7 to recompile the program
cd ../src         # Move to src folder
make              # Compile the program name "auction-system"
make clean        # Clean directory
cd ../test        # Move to test directory

# Declare location of the program (compiled under src folder)
program="../src/auction-system"
current_user_account="../src/Current_User_Accounts.txt"
available_items="../src/Available_Items.txt"
daily_transaction="../src/Daily_Transaction.txt"

# Using test in phase 1 run all the input one by one
# Then stores all of the output under actual_output folder
echo "\nGetting result outputs using the test inputs... \n"

# Clean directory before storing new actual_output
rm -rf ./actual_output/*

# Declare directory to be used
DIRECTORY=./input/

# For each file in the directory
for file in `find ${DIRECTORY} -type f`; do
   # Get file name only without extension
   DIR=`dirname ${file}`
   NAME=`basename ${file}`
   NEW=`echo ${NAME%%.*} | sed 's/[a-zA-Z_]\+\././'`
   #echo $NEW
   # Test the program by passing input files under input/fileName.txt
   # Then store the output to actual_output folder with format fileName.out
   # $program < ./input/$NEW.txt > ./actual_output/$NEW.out
   $program $current_user_account $available_items $daily_transaction < ./input/$NEW.txt > ./actual_output/$NEW.out
done

# Using expected output in phase 1, compare with the actual output
# If there are difference, potential error, fail the test case
echo "Testing results against expected outputs... \n"

# For each file in the directory
for file in `find ${DIRECTORY} -type f`; do
   # Get file name only without extension
   DIR=`dirname ${file}`
   NAME=`basename ${file}`
   NEW=`echo ${NAME%%.*} | sed 's/[a-zA-Z_]\+\././'`

   # Output
   FILE="${BLUE}Test for: ${NEW}${NC}"

   # If there is no difference between expected output and actual output, test passed, else test fail
   if diff -q -w -B ./actual_output/$NEW.out ./expected_output/$NEW.dat; then
      echo "\n$FILE - ${GREEN}PASS${NC}"
   else
      echo "\n$FILE - ${RED}FAIL${NC}"
   fi
done