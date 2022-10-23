#!/bin/bash

function die {
  echo "ERROR: $@"
  exit 1
}

[[ -f "2.3.h" ]] || die "File '2.3.h' not found"
sed 's/const//g' 2.3.h | sed 's/ *//g' | sed 's@//.*$@@g' | sed '/^$/d' \
  | diff /dev/stdin 2.3.ref.h > /dev/null \
  || die "You changed 2.3.h! You should only add 'const' keywords."
echo "First test PASSED: you didn't change 2.3.h other than adding 'const'"
