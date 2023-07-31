#!/usr/bin/env bash

# This file tests if code gives a 404 Not Found error if file doesn't exist.
port=$(bash ../test_files/get_port.sh)

# Start up server.
../httpserver $port > /dev/null &
pid=$!

# Wait until we can connect.
while ! nc -zv localhost $port; do
    sleep 0.01
done

for i in {1..5}; do
    # Make sure file doesn't exist.
    # It's... very unlikely someone will need a file called oogabooga.
    notafile="../oogaboogafile.txt"
    # Make sure file doesn't exist
    rm -rf $notafile

    # Expected status code.
    expected=404
    
    # The only thing that is should be printed is the status code.
    actual=$(curl -s -w "%{http_code}" -o /dev/null localhost:$port/$notafile)

    # Check the status code.
    if [[ $actual -ne $expected ]]; then
        # Make sure the server is dead.
        kill -9 $pid
        wait $pid
        exit 1
    fi

done

# Make sure the server is dead.
kill -9 $pid
wait $pid

exit 0
