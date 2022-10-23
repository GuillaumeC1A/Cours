#!/bin/bash

function die {
  echo "ERROR: $@"
  exit 1
}

g++ -std=c++11 -Wall -Wextra -Wno-sign-compare -O2 3.6.cc || die "Does not compile."

DATA="6,2,3
7,7
10,2,5
21,3,7
60,2,2,3,5
81,3,3,3,3
1073741824,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
1024384027,32003,32009
152415790094497781,123456791,1234567891
4611000000000000097,4611000000000000097
4000000044000000121,2000000011,2000000011
4000000088000000363,2000000011,2000000033
4611686018427387904,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
2,2
1,1"

for i in $DATA; do
  echo ${i%%,*} | timeout 30 ./a.out | awk '{print}' 'ORS=,' | grep "${i#*,}" > /dev/null ||
    die "Failed decomposition test with: ${i%%,*}"
  echo "SUCCESS with: ${i%%,*}"
done

g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2 3.6.cc && echo "SUCCESS: No warning"
