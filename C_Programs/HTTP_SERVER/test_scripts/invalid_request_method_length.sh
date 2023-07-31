#!/usr/bin/env bash

# Objective:- Checks to see if the request type length i.e method request is within 8 chars
port=$(bash ../test_files/get_port.sh)

# Start up server.
../httpserver $port > /dev/null &
pid=$!

# Wait until we can connect.
while ! nc -zv localhost $port; do
    sleep 0.01
done

for i in {1..5}; do
    # Test input file.
    file="../test_files/frankenstein.txt"
    infile="tempfile.txt"
    outfile="outtempfile.txt"

    # Copy the input file.
    cp $file $infile
    
    # Expected status code.
    expected=400

    # The only thing that is should be printed is the status code.
    actual=$(curl -s -w "%{http_code}" -o $outfile -X getgEtgetgEt http://localhost:$port/$infile)
    
    # Check the status code.
    if [[ $actual -ne $expected ]]; then
        # Make sure the server is dead.
        kill -9 $pid
        wait $pid
        rm -f $infile $outfile
        exit 1
    fi
    
    # Clean up.
    rm -f $infile
done

# Make sure the server is dead.
kill -9 $pid
wait $pid

# Clean up.
rm -f $infile $outfile

exit 0
