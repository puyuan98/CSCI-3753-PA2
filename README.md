# CSCI-3753-PA2


#Contact information
Name: Puyuan Zhang
Email: puzh5232@colorado.edu
Student ID: 107207898

#Files Description
#part 1 file
helloModule.c
Makefile

#Part 2 file
charModule.c
Makefile

#part 3 file
test.c

lakka_character_module.c ( ./character/lakka_character_module.c )
the implementation of character device driver (for part 2)

test.c (./test/test.c) the implementation of test program (for part 3)

#Building Instructions (kernel modules)
use Makefile to build both part1 and part2 file
type make all to create .ko and other file
or use make clean to clean all create file
  

Building Instructions (for test program)
Change the current working directory to test.
type <gcc test.c> then we will get a.out file and run it

#Installing Instructions (for character module)
cd ./PA2
make clean
make all
insmod charModule.ko

mknod -m 777 /dev/lakka_character_device_file c 500 0
Then use dmesg to check installation。
Running test program
cd ./test
./a.out
follow the message box to complete rest wrok
