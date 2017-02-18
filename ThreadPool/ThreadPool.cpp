//
//  ThreadPool.cpp
//  ThreadPool
//
//  Created by BIBIN THOMAS on 2/17/17.
//  Copyright © 2017 tomkaith13. All rights reserved.
//

#include "ThreadPool.h"

//the wrapper function for calling a start of a job
void ThreadPool::threadFunc() {
    while(1) {
        Job currJob;
        { //scope of the conditional variable
            unique_lock<mutex> lck(mt);
            
            //wait until jobQueue is filled or if finished is set to true
            cv.wait(lck, [this]() -> bool { return this->jobQueue.size() || this->finished; });
            
            //once finished is true, and the queue is empty, we exit the thread
            if (this->finished && this->jobQueue.empty())
                return;
            
            currJob = std::move(jobQueue.front());
            jobQueue.pop_front();
        }
    
        currJob.start();
    } //end while
}

ThreadPool::ThreadPool(int threadCount) {
    tCount = threadCount;
    finished = false;
    
    for (int i = 0 ; i < tCount; i++) {
        threadARR[i] = thread(&ThreadPool::threadFunc, this);
    }
    
}

ThreadPool::~ThreadPool() {
    //join all threads spun
    for (int i =0; i <tCount; i++)
        threadARR[i].join();
}

void
ThreadPool::AddJob(Job j) {
    { //scope for locking the queue mutex before pushing in a job
        unique_lock<mutex> guard(mt);
        jobQueue.push_back(j);
    }
    //signal that a job has been entered to one of the threads
    cv.notify_one();
}

void ThreadPool::wrapUp() {
    
    // locking and setting finished to true to signal a wrapup
    unique_lock<mutex> lck(mt);
    finished = true;
}
