#!/bin/bash

npm i -g http-server

chmod +x utility/build.sh
./utility/build.sh

cd browser || exit
http-server -p 54367 -c 315360000 &
SERVER_PID=$!

cleanup() {
    echo "Stopping the server..."
    kill $SERVER_PID
    exit 0
}

trap cleanup SIGINT

sleep 2
echo "You may start the debug session in your IDE..."

wait $SERVER_PID