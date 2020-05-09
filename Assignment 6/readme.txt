Output of the make clean check:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m47.517s
user    0m47.507s
sys     0m0.001s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m23.933s
user    0m47.602s
sys     0m0.007s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m13.910s
user    0m54.460s
sys     0m0.004s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m9.872s
user    1m16.631s
sys     0m0.010s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done

After running the make clean check, I observed that the real time, or
execution time, decreases with more threads when parallelizing the 
program and every test decreased by about half every time. The user time 
and the system time increases when the number of threads increases, 
since when there are more threads, each thread has system calls to
make and the total number of system calls increases.

Thus, I can say that my implementation of SRT improved the performace
of the program in terms of the execution time and parallelizing 
certain functions can improve time since multiple processes can 
occur at the same time instead of performing everything sequentially.

While parallelizing the program, I ran into some problems. First I was
trying to print the pixels in the separate function I made which is the 
function each thread performs. However, this creates a problem regarding
the race condition, since some threads might finish before others
and the CPU might do weird things. So it is necessary to know that all 
the threads are finished using the pthread_join function before you 
print anything out. However, to access the information in the function,
I needed to created a matrix as a global variable so I can print the 
pixels out in my main function instead of the calculate function. I 
also had to make the nthreads varaible global, so I could access it 
in the compare function I made, and renamed it to numthreads. 

Also, I had a problem of passing in more than one argument into the 
pthread function, since I need a variable to keep track of the 
thread and I need to pass in a scene_t variable that is initialized
in the main function. To fix this, I made a struct Args, which
had an int identification variable and a scene_t variable.

I was also having a problem when I used the command make clean check
command, and it was not recognizing the pthread functions. I fixed 
this by going to the Makefile and adding -lpthread. 

When I ran the make clean check command then, I was getting error 1, 
meaning the test had failed, and the output was all 0's. After searching
through my code, I realized I had forgot to remove the intialization
of the numthreads variable in the main function after adding numthreads
as a global variable. I also ran into the problem of not correctly
casting my thread_num variable in the calculate function, since I needed
to set px to an int and I was giving it an address instead since I didn't
add the pointer cast to the argument.  
