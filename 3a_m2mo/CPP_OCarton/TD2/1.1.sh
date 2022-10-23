#!/bin/bash

FILE="1.1.cc"
TEST="1.1.test.cc"

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
g++ -std=c++11 tmp.o $TEST || die "'$FILE' doesn't implement its API properly"
echo "PASSED: '$FILE' has the right API"
./a.out | egrep "(^|[^0-9])5214($|[^0-9])" > /dev/null || die "'$FILE' does not work as expected"
echo "PASSED: '$FILE' has the right behavior"
