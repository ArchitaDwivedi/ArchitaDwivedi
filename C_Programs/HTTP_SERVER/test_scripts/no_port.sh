#!/usr/bin/env bash

# This code tests to see if the port number is given!
# Start up server.
../httpserver > /dev/null 2>&1


if  [ $? = 0 ]
then
	exit 1
fi
exit 0
