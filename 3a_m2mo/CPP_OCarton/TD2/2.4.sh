#!/bin/bash

FILE="2.4.cc"
TEST="2.4.test.cc"

function die {
    echo "ERROR: $@"
        exit 1
}

function check_file {
    [[ -f "$1" ]] || die "FILE '$1' not found"
}

check_file $FILE
check_file $TEST

g++ -std=c++11 -c $FILE || die "'$FILE' does not compile alone."
g++ -std=c++11 $TEST || die "'$FILE' did not declare the proper API"
egrep "for|while|do" "$FILE" > /dev/null && die "Your function isn't recursive! loop detected in '$FILE'"
./a.out
