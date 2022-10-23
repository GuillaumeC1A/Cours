#!/bin/bash

function die {
  echo "ERROR: $@"
  exit 1
}

g++ -std=c++11 -Wall -Wextra -Wno-sign-compare -O2 3.3.cc || die "Does not compile."

PRIMES="3 5 7 11 13 17 23 10007"
COMPOSITES="4 6 14 25 10201 10403"

LPRIMES="2000000011 2000000033 2"
LCOMPOSITES="2000000001 2117932441 2118208567"

LLPRIMES="1000000000000000003 4000000044000000041 4611000000000000097"
LLCOMPOSITES="1000000000000000001 4611000000000000096 4000000044000000121 4000000088000000363"

t=0
for len in "" "L" "LL"; do
  tt=1
  [[ "$len" == "LL" ]] && tt=30
  var="${len}PRIMES"
  for n in ${!var}; do
    echo $n | timeout $tt ./a.out | grep "premier" > /dev/null || die "Failed with prime number $n"
  done
  var="${len}COMPOSITES"
  for n in ${!var}; do
    echo $n | timeout $tt ./a.out | grep "composite" > /dev/null || die "Failed with composite number $n"
  done
  ((t=t+1))
  echo "SUCCESS: tests $t/3"
done

g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2 3.3.cc && echo "SUCCESS: No warning"
