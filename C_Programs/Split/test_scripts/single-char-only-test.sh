../split ../test_files/frankenstein.txt *
if [ $? = 0 ]
then
	exit 1
fi


../split ../test_files/frankenstein.txt ~
if [ $? = 0 ]
then
	exit 1
fi
