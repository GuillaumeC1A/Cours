#!/bin/bash

FILE="3.1.cc"

function die {
    echo "ERROR: $@"
        exit 1
}

function check_file {
    [[ -f "$1" ]] || die "FILE '$1' not found"
}

check_file "$FILE"

sed 's/\s//g' "$FILE" | egrep -A 4 "^voidGetDate" > tmp
echo "voidGetDate(int*year,int*month,int*day){
*year=2018;
*month=9;
*day=19;
}" > ref
diff tmp ref > /dev/null || die "You changed the function void GetDate() in 3.1.cc!"
g++ -std=c++11 $FILE || die "'$FILE' does not compile."
echo "PASSED: '$FILE' compiles"

sed -i "s/\*year = 2018;/*year = 7654;/" "$FILE"
sed -i "s/\*month = 9;/*month = 11;/" "$FILE"
sed -i "s/\*day = 19;/*day = 22;/" "$FILE"

g++ -std=c++11 $FILE || die "'$FILE' does not compile when tweaked."

./a.out | grep "7654-11-22" > /dev/null || die "'$FILE' does not work as expected"
echo "PASSED: '$FILE' has the right behavior"
