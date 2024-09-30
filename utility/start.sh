#!/bin/bash

npm i -g http-server

chmod +x utility/build.sh
./utility/build.sh

cd browser || exit
http-server -p 54367 &
SERVER_PID=$!

sleep 0.5
cd ../

./build/Purr

kill $SERVER_PID
exit 0