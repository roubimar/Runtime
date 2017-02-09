//
//  frame.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "frame.hpp"
#include "objectHeap.hpp"

Frame::Frame(ClassFile * classFile, string method_name, string method_description, ObjectHeap * objectHeap) {
    this->classFile = classFile;
    this->method_name = method_name;
    this->method_description = method_description;
    this->objectHeap = objectHeap;
    pc = 0;
    
    if(!(classFile -> getMethod(method_name, method_description). access_flags & ACC_NATIVE ))
    {
	maxLocals = classFile ->  getMethod(method_name, method_description) . code_attr -> max_locals;
    } else {
        maxLocals = 1;
    }
    
    initLocalVar();
    
}


Frame::~Frame()
{
	while( !operandStack.empty())
    {
        operandStack.pop();
    }
    
    delete [] localVariables;
}

int Frame::increasePc(int step)
{
    pc += step;
    return pc;
}

/**
 * Ulozeni Operandu na heapu
 * @param index: index promenne v localVar
 * @param operand: Operand k ulozeni
 */
void Frame::storeVariable(int index, Operand* operand)
{
    // Otakza jestli neni lepsi najit neve prazdne misto a mazani nechat na GC
    delete objectHeap -> heap[localVariables[index]];
    objectHeap -> heap[localVariables[index]] = operand;
}

/**
 * nacteni operandu z localVar
 * @param index: index promenne v localVar
 * @return Operand na pozici indexu
 */
Operand * Frame::loadVariable(int index)
{
    return objectHeap -> heap[localVariables[index]];
}

/**
 * inicializace lokalnich promennych, do pole localVariables se ulozi index 
 * Operandu, ktery predstavuje danou promennou
 */
void Frame::initLocalVar()
{
    localVariables = new int[maxLocals];
    for(int i = 0; i < maxLocals; i++)
    {
        localVariables[i] = objectHeap -> createOperand();
    }
}
