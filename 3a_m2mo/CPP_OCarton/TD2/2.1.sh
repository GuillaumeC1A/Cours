#!/bin/bash

FILE="2.1.cc"
TEST="2.1.test.cc"

function die {
    echo "ERROR: $@"
        exit 1
}

function check_file {
    [[ -f "$1" ]] || die "FILE '$1' not found"
}

check_file $FILE
check_file $TEST

g++ -std=c++11 -c $FILE -o tmp.o || die "'$FILE' does not compile alone"
g++ -std=c++11 $TEST || die "'$FILE' did not declare the proper API"
egrep "for|while|do" "$FILE" > /dev/null && die "Your function isn't recursive! loop detected in '$FILE'"
./a.out | egrep "(^|[^0-9])326143996($|[^0-9])" > /dev/null || die "'$FILE' does not work as expected: wrong result!"
echo "PASSED: '$FILE' has the right behavior"
