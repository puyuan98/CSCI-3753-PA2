# CSCI-3753-PA2


#Contact information<br>
Name: Puyuan Zhang<br>
Email: puzh5232@colorado.edu<br>
Student ID: 107207898<br>

#Files Description<br>
#part 1 file<br>
helloModule.c<br>
Makefile<br>

#Part 2 file<br>
charModule.c<br>
Makefile<br>

#part 3 file<br>
test.c<br>

lakka_character_module.c ( ./character/lakka_character_module.c )<br>
the implementation of character device driver (for part 2)<br>

test.c (./test/test.c) the implementation of test program (for part 3)<br>

#Building Instructions (kernel modules)<br>
use Makefile to build both part1 and part2 file<br>
type make all to create .ko and other file<br>
or use make clean to clean all create file<br>
<br>
<br>
Building Instructions (for test program)<br>
Change the current working directory to test.<br>
type <gcc test.c> then we will get a.out file and run it<br>
<br>
#Installing Instructions (for character module)<br>
cd ./PA2<br>
make clean<br>
make all<br>
insmod charModule.ko<br>

mknod -m 777 /dev/lakka_character_device_file c 500 0<br>
Then use dmesg to check installation.<br>
Running test program<br>
cd ./test<br>
./a.out<br>
follow the message box to complete rest wrok<br>
