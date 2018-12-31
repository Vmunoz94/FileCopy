---   README   ---

In order to build the project, first you must clone the project using the terminal.

     git clone https://github.com/csc415-02-sp18/csc415-p2-Vmunoz94.git

Building this program required importing three header files.
The first file imported was <stdio.h>, which allows us to use the sprintf() system call.
The second file is <unistd.h>, which allows us to use the read() and write() system calls
in order to copy the contents of one file onto another file.
I used #define to represent my name. The last header file imported was <fcntl.h>,
this allows us to open the files and determine what we should do with these files.
We choose the flags when we initially open files. The file in which we are copying
from, should be read only because we do not want to write in the file we want to copy.
To do this we set the flag to be "O_RDONLY", which means read only. On the other hand,
The file we are copying too, should be write only because we want to write the contents
of the other file to this file. We do this by setting the flag to be O_WRONLY, which means
write only. I also added another flag O_TRUNC, which basically creates an exact copy
of the original file. With out this other flag, the contents of the original file
will only be added to the beginning of the contents of the second file. Lastly, we
should properly close the files.

**Things to note**
-    O_CREAT can also be added as a flag, which creates a file by the same name if the
     file does not already exist.

In order to run the project, first you must compile the code in the terminal,

     gcc filecopy.c

then execute the code in order to run it in the terminal.

     ./a.out

The code simply copies the content from one file, to another and creates an exact copy.
If the source file does not exist, the program terminates. If the destination file does
not exist, then the program terminates.

I use a mac for all my programming projects, and for this project we were asked to
run our program using the strace utility; however, mac's OSX does not have strace.
Mac's have something called dtruss, which tracks a programs system calls, but this
was disabled after the el capitan software update on macs.
In order for me to use strace to track the system calls my program does, I used
the Linux Mint 64-bit virtualbox VM to compile and run my program using strace.
On the Linux Mint machine, I compiled my program exactly how I would on my mac.
However, to execute and run the program with strace counting the amount of system calls
my program does, I typed.

     strace -c ./a.out

This runs the program normally and at the very end it shows the amount of
system calls performed. In my code, on lines 77-95, the destination file is being
overwritten 27 bytes at a time. This causes a system call from read() and a system
call from write(). So for each set of 27 bytes, there are two system calls. Which is shown
using strace, the total system calls is almost equal to double the amount of bytes copied
divided by 27. 

File Copy Successful, 2992 bytes copied
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 57.60    0.000307           3       116           write
 42.40    0.000226           2       115           read
  0.00    0.000000           0         4           open
  0.00    0.000000           0         4           close
  0.00    0.000000           0         3           fstat
  0.00    0.000000           0         1         1 lseek
  0.00    0.000000           0         7           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         3         3 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000533                   263         4 total
