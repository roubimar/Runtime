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
    
    stack.push(initFrame);
    
}

// Vykonání nejvrchnějšího framu
void FrameStack::execute()
{
    Frame * executedFrame = stack.top();
    
    method_info_w_code method = classFile->getMethod(executedFrame->method_name, executedFrame->method_description);
    executedFrame->localVariables.reserve((int)method.code_attr->max_locals);
    
    for (int i = 0; i == method.code_attr->max_locals; i++) {
        executedFrame->localVariables[i] = nullptr;
    }
    
    // Code pointer
    u1 * p = method.code_attr->code;
    while(true)
    {
        switch (p[executedFrame->pc]) {
            case 0x00:
                executedFrame->increasePc(1);
                break;
            case 0x1b: //iload_1
            {
                executedFrame->operandStack.push(executedFrame->localVariables[1]);
                executedFrame->increasePc(1);
                break;
            }
            case 0x1c: //iload_2
            {
                executedFrame->operandStack.push(executedFrame->localVariables[2]);
                executedFrame->increasePc(1);
                break;
            }
            case 0x3c: //istore_1
            {
                executedFrame->localVariables[1] = executedFrame->operandStack.top();
                executedFrame->operandStack.pop();
                executedFrame->increasePc(1);
                break;
            }
            case 0x3d: //istore_2
            {
                executedFrame->localVariables[2] = executedFrame->operandStack.top();
                executedFrame->operandStack.pop();
                executedFrame->increasePc(1);
                break;
            }
            case 0x3e: //istore_3
            {
                executedFrame->localVariables[3] = executedFrame->operandStack.top();
                executedFrame->operandStack.pop();
                executedFrame->increasePc(1);
                break;
            }
            case 0x04: //iconst_1
            {
                Operand * intOp = new Operand(1);
                executedFrame->operandStack.push(intOp);
                executedFrame->increasePc(1);
                break;
            }
            case 0x05: //iconst_2
            {
                Operand * intOp = new Operand(2);
                executedFrame->operandStack.push(intOp);
                executedFrame->increasePc(1);
                break;
            }
            case 0x60: //iadd
            {
                int firstOp = executedFrame->operandStack.top()->value;
                executedFrame->operandStack.pop();
                
                int secondOp = executedFrame->operandStack.top()->value;
                executedFrame->operandStack.pop();
                
                Operand * result = new Operand(firstOp + secondOp);
                executedFrame->operandStack.push(result);
                executedFrame->increasePc(1);
                break;
            }
            case 0xb1: //return
                stack.pop();
                return;
                
            default:
                break;
                
        }
    }
    
    
}
