#!/bin/bash

function die {
  echo "ERROR: $@"
  exit 1
}

g++ -std=c++11 -Wall -Wextra -Wno-sign-compare -O2 2.cc || die "Does not compile."
line=2
for i in 18.9979 18.4207 0.577216 0.499865; do
  ./a.out | awk "FNR==$line "'{print $2}' 'FS=:' | grep $i  > /dev/null || die "Unexpected value at line #$line of your program's output."
  echo "SUCCESS: line #$line contains the expected value."
  ((line = line+1 ))
done
g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2 2.cc && echo "SUCCESS: no warnings"
