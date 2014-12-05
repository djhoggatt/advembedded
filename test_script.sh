#!/bin/bash

# Spencer Clegg -- spencermclegg@gmail.com -- Nov 2014
# usage: watch -n 1 ./test_script.sh
# Runs test with driver.o in a loop only showing diff of CMVs

# Chooose parameters 
./test > output.tmp
# ./test maxpoints=3 > output.tmp

# LIC8 Fails with this...
#./test seed=3887884696  maxpoints=100 > output.tmp

# LIC6 Fails with this...
#./test seed=386001650  maxpoints=100 > output.tmp


# Show CMV Diffs or all Diffs
awk '/testcase/ || /CMV/ || /match/ || /PUM/ {print}' output.tmp > filtered.tmp
# tail -n +5 output.tmp > filtered.tmp

# split file into multiple files
csplit -sz -n 1 -f split filtered.tmp /testcase/ {*}

# Diff the last (failed) test case
my_file=$(ls -1v split* | tail -1)
his_file=$(ls -1v split* | tail -2 | head -1)
diff -y --suppress-common-lines $his_file $my_file

# Cleanup
rm -rf *.tmp split? split??
                                                                                                                                                                                                                                              