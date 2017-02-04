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
#include "objectHeap.hpp"
#include "classHeap.hpp"
#include "classFile.hpp"

#include <stdio.h>
#include <stack>

using namespace std;

class FrameStack{
    public:
        // Proměnné
        stack<Frame*> framesStack;
        ClassFile * classFile;
        Frame * actualFrame;
        ObjectHeap * objectHeap;
        ClassHeap  * classHeap;
        u1 * p;
        // Metody
        FrameStack(ClassFile * classFile, ObjectHeap *objectHeap, ClassHeap * classHeap);
        ~FrameStack();
        void execute();
    
        // Instrukce
        void def();
        void ret();

        // Integer
        void iadd();
        void iload(int index);
        void aload(int index);
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
        void ifIcmpgt(u1 * p);
        void ifIcmpeq(u1 * p);
        void ifIcmpne(u1 * p);
        void ifIcmpge(u1 * p);
        void ifIcmplt(u1 * p);
        void ifIcmple(u1 * p);
        void _goto(u1 * p);
        void invoke(u1 * p, bool lessParams);
        u2 getNumberOfMethodParams(string p_description);
        u4 _new(u1 * p);
        void ldc();
        int loadConstant(u1 * p);
        void iinc(u1 * p);
        void executeNativeMethod();
        void printString();
        void printInt();
        void readString();
        void dup();
        void pop();
        void getStatic();
      


        void ifConditionIncreasePc(bool result, u1 * p);
        
};

#endif /* frameStack_hpp */
