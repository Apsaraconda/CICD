#!/bin/bash

if [[ $CI_JOB_STATUS == 'success' ]]; then
    CI_JOB_STATUS="SUCCESS!✅"
else
    CI_JOB_STATUS="FAILED!❌"
fi

TELEGRAM_BOT_TOKEN="TELEGRAM_BOT_TOKEN"
TELEGRAM_USER_ID="TELEGRAM_USER_ID"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Author:+$CI_COMMIT_AUTHOR%0A%0AJob name: $CI_JOB_NAME%0A%0AStatus:+$CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME"

curl -s -d "chat_id=$TELEGRAM_USER_ID&text=$TEXT" $URL > /dev/null