//
//  ThreadPool.h
//  ThreadPool
//
//  Created by BIBIN THOMAS on 2/17/17.
//  Copyright © 2017 tomkaith13. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h
#include <iostream>
#include <stdio.h>
#include <deque>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Job.h"
using namespace std;
#define TP_MAX_THREADS 25




// Thread pool class
class ThreadPool {
    // nums of threads in the pool
    int tCount;
    
    //doubly ended Queue for storing the jobs
    deque<Job> jobQueue;
    
    //flag to indicate that we are done with the thread pool and signalling a wrap up
    bool stopAccepting = false;
    
    //Thread arr used by the ctor
    thread threadARR[TP_MAX_THREADS];
    
    //Thread synchronization objects
    mutex mt;
    condition_variable cv;
    
    
    
public:
    ThreadPool(int tCount);
    void AddJob(Job);
    void* getResult(int jId);
    void threadFunc();
    void stopReceivingJobs();
    const inline int getJobQLen() { unique_lock<mutex> lck(mt); return (int)jobQueue.size(); }
    ~ThreadPool();
    
};

#endif /* ThreadPool_h */
