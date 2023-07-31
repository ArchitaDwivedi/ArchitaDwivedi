../split ../test_files/emptyfile.txt a
if [ $? = 1 ]
then
   exit 1
fi
