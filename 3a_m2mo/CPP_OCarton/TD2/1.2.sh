#!/bin/bash

FILE="1.2.main.cc"
TEST="1.2.ref.cc"

function die {
    echo "ERROR: $@"
        exit 1
}

function check_file {
    [[ -f "$1" ]] || die "FILE '$1' not found"
}

check_file $FILE
check_file $TEST

g++ -std=c++11 -c $FILE -o tmp.o || die "'$FILE' does not compile."
echo "PASSED: '$FILE' compiles"
g++ -std=c++11 $TEST tmp.o || die "'$FILE' does not link."
echo "PASSED: '$FILE' links"
./a.out | egrep "(^|[^0-9])5681($|[^0-9])" > /dev/null || die "'$FILE' does not work as expected. Did you modify it too much?"
echo "PASSED: '$FILE' has the right behavior"
