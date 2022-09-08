#!/bin/bash

rm -f tests.out 2>&1 >/dev/null
gcc -g -Wall -Wextra -Wwrite-strings -oprog0 big_integer.c
input="./tests.in"
while IFS= read -r line
do
  echo "./prog0 $line"
  ./prog0 $line | tee -a tests.out
done < "$input"
diff -B -iw tests.reference tests.out
rc=$?
if [[ $rc == 0 ]]; then
  echo "All tests passed"
else
  echo "One or more tests failed"
fi
exit $rc
