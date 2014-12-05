#!/bin/bash

# Spencer Clegg -- spencermclegg@gmail.com -- Nov 2014
# usage: watch -n 1 ./test_script.sh
# Runs test with driver.o in a loop only showing diff of CMVs

# Output not sorted
# ./test > output.tmp
./test maxpoints=3 > output.tmp

# LIC8 Fails with this...
#./test seed=3887884696  maxpoints=100 > output.tmp

# LIC6 Fails with this...
#./test seed=386001650  maxpoints=100 > output.tmp


# only show CMV
awk '/testcase/ || /CMV/ || /match/ {print}' output.tmp > cmv_only.tmp

# split file into two files
csplit -sz -n 1 -f split cmv_only.tmp /testcase/ {*}


i="9"

while [ $i -ge 0 ]; do
  if [ -f split$i ]; then
    # echo "split$[ $i-1 ] split$i"  
    diff -y --suppress-common-lines split$[ $i-1 ] split$i 
	diff -y --suppress-common-lines split$[ $i-1 ] split$i > diff_out.txt
    break
  else
  i=$[$i-2]
  fi
done

# Cleanup
# rm -rf *.tmp split?
