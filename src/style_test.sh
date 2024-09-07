#!/bin/bash

clang_result=$(clang-format -n -style=Google ./*/*.c ./*/*.h)
if [ ${#clang_result} -gt 0 ]; then
  echo "Style test fail!"
  echo $clang_result
  exit 1
else
  echo "Style test success!"
fi
