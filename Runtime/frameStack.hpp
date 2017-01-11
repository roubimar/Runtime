//
//  FrameStack.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#ifndef frameStack_hpp
#define frameStack_hpp

#include "frame.hpp"

#include <stdio.h>
#include <stack>

using namespace std;

class FrameStack{
    public:
        // Proměnné
        stack<Frame*> stack;
        ClassFile * classFile;
    
        // Metody
        FrameStack(ClassFile * classFile);
        void execute();
};

#endif /* frameStack_hpp */
