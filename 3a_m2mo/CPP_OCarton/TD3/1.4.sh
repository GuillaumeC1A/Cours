#!/bin/bash

FILE="1.4.cc"
TEST="1.4.test.cc"

function die {
    echo "ERROR: $@"
        exit 1
}

function check_file {
    [[ -f "$1" ]] || die "FILE '$1' not found"
}

check_file "$FILE"
check_file "$TEST"

g++ -std=c++11 $TEST || die "'$FILE' does not compile with '$TEST'."
echo "PASSED: '$FILE' compiles"
./a.out
