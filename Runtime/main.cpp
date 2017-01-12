//
//  main.cpp
//  Run
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include <iostream>
#include <stack>

#include "./classFile.hpp"
#include "./classHeap.hpp"
#include "./frameStack.hpp"

using namespace std;

int main(int argc, char * argv[]){
    
    
    ClassHeap  * classHeap = new ClassHeap();
    FrameStack * frameStack;

    
    try {
        frameStack = new FrameStack(classHeap->getClass("Main"));
        
        frameStack->execute();
        
    } catch(int e) {
        if(e == 21) cout << "Out of memory exception" << endl;
        else if( e == 25) cout << "Class file load failed. Maybe wrong Class file name?" << endl;
        else cout << "Exception " << e << " occured" << endl;
        return 1;
    }
    
    cout << "DonexXxX: " << endl;

    delete classHeap;
    printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
    delete frameStack;
    return 0;

    
}
