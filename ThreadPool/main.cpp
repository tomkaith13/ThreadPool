//
//  main.cpp
//  ThreadPool
//
//  Created by BIBIN THOMAS on 12/13/16.
//  Copyright © 2016 tomkaith13. All rights reserved.
//


#include "ThreadPool.h"

using namespace std;




void* workLoad(void* arg) {
    struct threadArg {
        int res;
    };
    
    struct threadArg tArg = *(struct threadArg*)arg;
    cout<<"id:"<<tArg.res<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return nullptr;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    ThreadPool t(10);
    struct threadArg {
        int res;
    };
    
    threadArg tArg[100];

    for (int i = 0; i < 100; i++) {
        tArg[i].res = i;
       (void) t.AddJob(Job(workLoad, &tArg[i]));
    }

    // used more for like congestion control of job submissions
    t.stopReceivingJobs();
    
    //std::this_thread::sleep_for(std::chrono::seconds(4));
    
    // restart adding more jobs
    t.restartReceivingJobs();
    threadArg tArg2[100];
    
    for (int i = 0; i < 100; i++) {
        tArg2[i].res = i+100;
        (void) t.AddJob(Job(workLoad, &tArg2[i]));
    }
    
    return 0;
}
