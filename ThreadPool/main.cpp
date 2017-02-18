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
    //int s = *(int*) arg;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return nullptr;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    ThreadPool t(10);
    
    for (int i = 0; i < 100; i++)
       t.AddJob(Job(i, workLoad, &i));

    
    t.wrapUp();
    
    
    return 0;
}
