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
        stack<Frame*> framesStack;
        ClassFile * classFile;
        Frame * actualFrame;
    
        // Metody
        FrameStack(ClassFile * classFile);
        ~FrameStack();
        void execute();
    
        // Instrukce
        void def();
        void ret();

        // Integer
        void iadd();
        void iload(int index);
        void iaload();
        void istore(int index);
        void iconst(int constant);
        void idiv();
        void ineg();
        void ireturn();
        void imul();
        void ifeq(u1 * p);
        void ifne(u1 * p);
        void iflt(u1 * p);
        void ifge(u1 * p);
        void ifgt(u1 * p);
        void ifle(u1 * p);


        void ifConditionIncreasePc(bool result, u1 * p);
        
};

#endif /* frameStack_hpp */
