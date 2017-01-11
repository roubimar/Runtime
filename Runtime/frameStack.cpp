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

// Vykonání nejvrchnějšího framu
void FrameStack::execute()
{
    actualFrame = framesStack.top();
    
    method_info_w_code method = classFile->getMethod(actualFrame->method_name, actualFrame->method_description);
    actualFrame->localVariables.reserve((int)method.code_attr->max_locals);
    
    for (int i = 0; i == method.code_attr->max_locals; i++) {
        actualFrame->localVariables[i] = nullptr;
    }
    
    // Code pointer
    u1 * p = method.code_attr->code;
    while(true)
    {
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
    int firstOp = actualFrame->operandStack.top()->value;
    actualFrame->operandStack.pop();
    
    int secondOp = actualFrame->operandStack.top()->value;
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp + secondOp);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::def()
{
    actualFrame->increasePc(1);
}

void FrameStack::iload(int index)
{
    actualFrame->operandStack.push(actualFrame->localVariables[index]);
    actualFrame->increasePc(1);
}

void FrameStack::istore(int index)
{
    actualFrame->localVariables[index] = actualFrame->operandStack.top();
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
}
