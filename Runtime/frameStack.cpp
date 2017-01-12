//
//  FrameStack.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "frameStack.hpp"


// Konsturktor
FrameStack::FrameStack(ClassFile * classFile)
{
    this->classFile = classFile;
    Frame * initFrame = new Frame(classFile, "main", "([Ljava/lang/String;)V");
    
    framesStack.push(initFrame);
    
}

FrameStack::~FrameStack(){
    while( !framesStack.empty())
    {
        framesStack.pop();
        printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    }
    delete classFile;
}

// Vykonání nejvrchnějšího framu
void FrameStack::execute()
{
    actualFrame = framesStack.top();
    
    method_info_w_code method = classFile->getMethod(actualFrame->method_name, actualFrame->method_description);
    
    // Code pointer
    u1 * p = method.code_attr->code;
    while(true)
    {
        // Vykonání jedné instrukce
        switch (p[actualFrame->pc]) {
            case 0x00:
                
                break;
            case 0x1b: //iload_1
            {
                iload(1);
                break;
            }
            case 0x1c: //iload_2
            {
                iload(2);
                break;
            }
            case 0x3c: //istore_1
            {
                istore(1);
                break;
            }
            case 0x3d: //istore_2
            {
                istore(2);
                break;
            }
            case 0x3e: //istore_3
            {
                istore(3);
                break;
            }
            case 0x04: //iconst_1
            {
                iconst(1);
                break;
            }
            case 0x05: //iconst_2
            {
                iconst(2);
                break;
            }
            case 0x60: //iadd
            {
                iadd();
                break;
            }
            case 0xb1: //return
                ret();
                return;
                
            default:
                break;
                
        }
    }
}

void FrameStack::iadd()
{
    Operand* firstOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand* secondOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp -> value + secondOp -> value);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::def()
{
    actualFrame->increasePc(1);
}

void FrameStack::iload(int index)
{
    actualFrame->operandStack.push(actualFrame->loadVariable(index));
    actualFrame->increasePc(1);
}

void FrameStack::istore(int index)
{
    actualFrame->storeVariable(index, actualFrame->operandStack.top());
    actualFrame->operandStack.pop();
    actualFrame->increasePc(1);
}

void FrameStack::iconst(int constant)
{
    Operand * intOp = new Operand(constant);
    actualFrame->operandStack.push(intOp);
    actualFrame->increasePc(1);
}

void FrameStack::ret()
{
    framesStack.pop();
    delete actualFrame;
}
