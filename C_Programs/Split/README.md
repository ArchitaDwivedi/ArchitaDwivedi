# CSE130 - Assignment 0 : Split

This program is about splitting file(s) based on the given delimiter!


## List of files:

The program directory should include:

```
README.md - Details about the program.

split.c - Main program file (source code),

Makefile - To make (compile, clean, format, etc.) the code.

test_files - This is a directory, that contains the files that maybe required by the scripts in test_scripts.

test_scripts - This is a directory that contains the test scripts.
```

## How to run the program:

Make sure  you're in the directory where 'split.c' and 'Makefile' exists and run the following command
```
make (you could also use - make all)
```

Next, run the following command and make sure to replace <filename(s)> with your actual filenames and <delimiter> with an actual delimiter of your choice.

```
./split <filename(s)> <delimiter>
```


## About the Test Scripts

The 'test_scripts' directory has all the scripts. These are meant to run from within the 'test_script' directory itself and you do not need to move them elsewhere.

The files that these test scripts use internally are available in the 'test_files' directory and a few of those files are the same as the ones we were provided with on github by the professor!


What each test script tests for:
```
1) space-test.sh :- This script is checking 'split' on a space i.e  " ".

2) single-char-only-test.sh :- This script checks if 'split' returns the error/warning related to the use of single character delimiters in case of special characters.

3) not-enough-args-test.sh :- This script checks if 'split' returns the error/warning related to not using enough arguments in case of special characters.

4) empty-test.sh :- This script checks the case when an empty file is provided to 'split'.

```


## Program Design
The program consists of a char array of size 4096 (Please refer to the next section for more details). From the command line, we pick up the list of files and the delimiter.

First, we go through a test that checks whether or not we have been provided with enough arguments for the program to run in the first place! If not we return, else we continue.
Then we check if the last argument is a single character!


If both these cases pass, we move onto the main execution of the program! 

We start by looping over all the list of files we have...

 -If the file name is '-', then we read input from stdin into the buffer, modify the buffer 
  accordingly in a loop and then once modified, we write it back to stdout and clear the buffer 
  for the next set of input until eof is encountered!

 -If the file name is a normal name, then we open the file if it exists or else move onto the next file, read the content of the file into the buffer. Then we modify the buffer in a loop accordingly and once modified we write it back to stdout and clear the buffer for the next set of input until all the contents from the opened file is not yet completely. Once it is completed read, we close that file and move onto the next file until all file are dealt with!


more size reading = more cpu usage
## How Buffer Size was chosen:
As per this [source](https://stackoverflow.com/questions/236861/how-do-you-determine-the-ideal-buffer-size-when-using-fileinputstream), I noted that the file system's buffer size is what is the ideal block size but I wanted to further investigate this.
Firstly, for the linux file system, the default block size is 4096 Bytes. 

So what do you mean by block size?

When we do the I/O operations, say read, we read in blocks i.e in linux we would read about 4096 bytes by default. 
Now we definitely could use read more than 4096 bytes if we wanted but there is a problem. When we try to read more than what is advised by default, even though the overall clock time (real time) for the program will reduce, we will be compromising our CPU usage i.e there will be a load on our CPU !

On the other hand, if we try to read less than what is advised, even though the the CPU usage reduces , our program will execute very slowly i.e the real time will increase significantly!


To test this out, I ran the 'time' command in linux on split as follows:

```
For buffer size of 16,384 B, (larger than default/advised)

time ./split foo.txt a


output -->   real time was 26 seconds and CPU time (user + sys) was 16 seconds

```


```
For buffer size of 4096 B (default advised size!)
(default filesystem block size),


time ./split foo.txt a


output -->   real time was 52 seconds and CPU time (user + sys) was 14 seconds

```


```
For buffer size of 1000 B, (smaller than default/advised)


time ./split foo.txt a


output -->   real time was 89 seconds and CPU time (user + sys) was 11 seconds

```


## Conclusion on Buffer Size decision

As can be seen from the tests I performed above, the optimum choice is when we go by the default block size of the linux filesystem as we do not put excessive load on the CPU and do not have a large execution time as well i.e it is the optimum
choice in this case

I also, ran the time command on 'rsplit' i.e the split function provided to us by the professor and compared it with my 'split' file and the time difference was almost negligible  which is also a reason that contributed towards the 4096 B buffer size choice.


