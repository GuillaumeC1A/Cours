#!/bin/bash

function die {
  echo "ERROR: $@"
  exit 1
}

g++ -std=c++11 -Wall -Wextra -Wno-sign-compare -O2 3.2.cc || die "Does not compile."

# Randomized tests.
RANDOM="Deterministic seed"
for i in {1..100}; do
  (( a = $RANDOM % 12 + 2 ))
  (( b = $RANDOM % 13 + 1 ))
  ((c=a*b))
  echo "$c
$a" | ./a.out | grep "est divisible" > /dev/null || die "Failed with $c/$a"
  m=$RANDOM
  (( d = a*b + (m % (a-1)) + 1))
  echo "$d
$a" | ./a.out | grep "n'est pas divisible" > /dev/null || die "Failed with $d/$a"
done
echo "SUCCESS: Randomized tests."

# Corner cases
echo "12
4" | ./a.out | grep "est divisible" || die "Failed with 12/4"
echo "SUCCESS: 12/4"

echo "234567890
10" | ./a.out | grep "est divisible" || die "Failed with 23456789/10"
echo "SUCCESS: 23456789/10"

echo "234567890
3" | ./a.out | grep "n'est pas divisible" || die "Failed with 23456789/3"
echo "SUCCESS: 23456789/3"

echo "234567890
1" | ./a.out | grep "est divisible" || die "Failed with 23456789/1"
echo "SUCCESS: 23456789/3"

echo "32
64" | ./a.out | grep "n'est pas divisible" || die "Failed with 32/64"
echo "SUCCESS: 32/64"

echo "1
1" | ./a.out | grep "est divisible" || die "Failed with 1/1"
echo "SUCCESS: 1/1"

echo "0
1" | ./a.out | grep "est divisible" || die "Failed with 0/1"
echo "SUCCESS: 0/1"

echo "0
23456789" | ./a.out | grep "est divisible" || die "Failed with 0/23456789"
echo "SUCCESS: 0/23456789"

g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2 3.2.cc && echo "SUCCESS: No warning"
