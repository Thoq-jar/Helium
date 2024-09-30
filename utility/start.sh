#!/bin/bash

cd browser || exit
fuser -k 54367/tcp
http-server -p 54367 &
SERVER_PID=$!
your-browser &
sleep 0.5
cd ../
./build/Purr
kill $SERVER_PID
exit 0