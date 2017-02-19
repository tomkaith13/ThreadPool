# ThreadPool
A simple C++11 threadpool implementation 
using Class Job and Class ThreadPool

The library uses C++11 thread library making thread creation simpler
than using pthreads.

THREADPOOL:
Creating threads everytime we have a new Job to do is trivial. However, pthread_create
and all other thread creation function invoke a system call which is a huge cost 
(user-mode to kernel-mode execution switch), hence the best solution would be 
create the threads of size n and wake them up to pick up a job when they arrive. 
Thats the reason ThreadPools exists

Using this header file ThreadPool.h, we can do the following:

CREATION:
ThreadPool tp(5); // This create a pool of 5 threads and wait for you to add Jobs.

For adding jobs/tasks to the pool, we supply a Job Class object.
The Job class ctor takes 3 arguments: jobId(int), the function to call 
(via function pointers), and args to the function wrapped in a 
generic pointer(void*).

Eg:

void taskFunc() {
// task body
}

...

Job j(1, taskFunc, nullptr);



ADDING JOBS TO THREADPOOL:
This function is a boolean and will return if job addition was a success
or not.
tp.addJob(j);

This will finish cause one of the threads to pick of the job submitted,
finish it and await more submissions.


THREADPOOL STOP RECEIVING NEW JOBS:
The final functionality of the threadpool, is if we are done accepting new jobs 
and we are wrapping up the existing jobQueue entries
tp.stopReceivingJobs()

RESTART RECEIVING NEW JOBS:
This will help with reuse of existing thread pool by allowing
the job Queue to start accepting jobs again.
tp.restartReceivingJobs()
