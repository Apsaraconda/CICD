#!/bin/bash

# ssh-copy-id user@10.20.0.1
CAT_PATH="./src/cat/s21_cat"
GREP_PATH="./src/grep/s21_grep"

if ! [ -e $CAT_PATH ]; then
  echo "File $CAT_PATH is not exists!".
  exit 1
fi

if ! [ -e $GREP_PATH ]; then
  echo "File $GREP_PATH is not exists!".
  exit 1
fi

sshpass -p '1' scp -o StrictHostKeyChecking=no $CAT_PATH user@10.20.0.1:/home/user
sshpass -p '1' scp -o StrictHostKeyChecking=no $GREP_PATH user@10.20.0.1:/home/user
echo "Try to move files to /usr/local/bin/ ...".
sshpass -p '1' ssh -o StrictHostKeyChecking=no user@10.20.0.1 mv /home/user/s21_* /usr/local/bin/