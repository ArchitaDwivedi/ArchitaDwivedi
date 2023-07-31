#!/usr/bin/env bash

# This code checks to see if the file name is valid i.e [a-zA-Z0-9._]
port=$(bash ../test_files/get_port.sh)

# Start up server.
../httpserver $port > /dev/null &
pid=$!

# Wait until we can connect.
while ! nc -zv localhost $port; do
    sleep 0.01
done

for i in {1..5}; do
    # Make sure file doesn't exist and make it a directory.
    # It's... very unlikely students have a needed directory called oogabooga.
    wrongfilename="../fo-o.txt"
    touch $wrongfilename

    # Expected status code.
    expected=400
    # The only thing that is should be printed is the status code.
    actual=$(curl -s -w "%{http_code}" -o /dev/null http://localhost:$port/$wrongfilename)

    # Check the status code.
    if [[ $actual -ne $expected ]]; then
        # Make sure the server is dead.
        kill -9 $pid
        rm -rf $wrongfilename
        wait $pid
        exit 1
    fi


done

# Make sure the server is dead.
kill -9 $pid
wait $pid
rm -rf $wrongfilename

# In case they create the file.
exit 0
