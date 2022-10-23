#!/bin/bash
set -e
g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare 3.3.cc

in=" Bonjour  madame     la marquise H E L L O    W    ORL D  "
echo "Running: ./a.out "${in}""
out=$(./a.out "${in}")
expected="BonjourmadamelamarquiseHELLOWORLD"
if [[ "${out}" = "${expected}" ]]; then
  echo "Test 1 PASSED"
else
  echo "FAILED! Expected: ${expected}"
  echo "        Got     : ${out}"
  exit 1
fi

in="pa    pe t    i     peton"
echo "Running: ./a.out "${in}""
out=$(./a.out "${in}")
expected="papetipeton"
if [[ "${out}" = "${expected}" ]]; then
  echo "Test 2 PASSED"
else
  echo "FAILED! Expected: ${expected}"
  echo "        Got     : ${out}"
  exit 1
fi
echo "SUCCESS"
