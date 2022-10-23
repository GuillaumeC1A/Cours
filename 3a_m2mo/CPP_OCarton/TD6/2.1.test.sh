#!/bin/bash

function die {
  echo -e "ERROR: $@"
 exit 1
}

FILE=2.1.txt

[[ -f "$FILE" ]] || die "$FILE' not found"

echo "Detected file '$FILE' with $(cat $FILE | wc -l) lines"
EXP="1183452715,1552147931,3728085945"
LINE=0
for i in $(sed 's/ *//g' 2.1.txt  | sed 's/,//g'); do
  ((LINE += 1))
  E="${EXP%%,*}"
  EXP="${EXP#*,}"
  CK="$(echo "$i" | cksum)"
  if [[ "${CK% *}" == "$E" ]]; then
    echo "Line $LINE: Test PASSED"
  else
    echo "Line $LINE: FAILED (Your answer: $(head -n $LINE 2.1.txt | tail -n 1))"
  fi
done
