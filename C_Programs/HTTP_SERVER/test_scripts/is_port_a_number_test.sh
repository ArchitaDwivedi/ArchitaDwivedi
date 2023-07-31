#!/usr/bin/env bash
# This code tests to see if the port number format is correct i.e it is a string!
# Start up server.
../httpserver 11abc > /dev/null 2>&1

if  [ $? = 0 ]
then
	exit 1
fi

../httpserver abc > /dev/null 2>&1
if  [ $? = 0 ]
then
	exit 1
fi


../httpserver $% > /dev/null 2>&1
if  [ $? = 0 ]
then
	exit 1
fi

../httpserver $1 > /dev/null 2>&1
if  [ $? = 0 ]
then
	exit 1
fi

../httpserver 1%% > /dev/null 2>&1
if  [ $? = 0 ]
then
	exit 1
fi

exit 0
