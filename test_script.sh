#!/bin/bash

# Spencer Clegg -- spencermclegg@gmail.com -- Nov 2014
# usage: watch -n 1 ./test_script.sh
# Runs test with driver.o in a loop only showing diff of CMVs

# Chooose parameters 
#./test > output.tmp
# LIC8 False.. seed=4178373335 maxpoints=10 
./test seed=3379710800 maxpoints=10 > output.tmp
# LIC8 True: 
#./test maxpoints=10 > output.tmp
grep -i --color seed output.tmp
grep -i --color NUMPOINTS output.tmp
# Show CMV Diffs or all Diffs
awk '/testcase/ || /CMV/ || /match/ {print}' output.tmp > filtered.tmp
# tail -n +5 output.tmp > filtered.tmp

# split file into multiple files
csplit -sz -n 1 -f split filtered.tmp /testcase/ {*}

# Diff the last (failed) test case
my_file=$(ls -1v split* | tail -1)
his_file=$(ls -1v split* | tail -2 | head -1)

diff -y --suppress-common-lines $his_file $my_file > check.out
diff -y --suppress-common-lines $his_file $my_file

# Cleanup
# rm -rf *.tmp
rm -rf split*                                                                                                                                                                                                                                           