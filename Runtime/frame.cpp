//
//  frame.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "frame.hpp"

Frame::Frame(ClassFile * classFile, string method_name, string method_description) {
    this->classFile = classFile;
    this->method_name = method_name;
    this->method_description = method_description;
    pc = 0;
    
}


Frame::~Frame()
{
	while( !operandStack.empty())
    {
        operandStack.pop();
    }
<<<<<<< HEAD

for( vector<Operand*>::iterator i = localVariables.begin(), endI = localVariables.end(); i != endI; ++i)
{
	printf("dasdjiashdiuas\n");
   delete *i;
}
localVariables.clear();
=======
    for(map<int,Operand*>::iterator it = localVariables.begin(); it != localVariables.end(); it++)
    {
        delete it->second;
    }
    
    localVariables.clear();
>>>>>>> bf8f476a2985e9a4664495e6a5acbaa32d98984a
}

int Frame::increasePc(int step)
{
    pc += step;
    return pc;
}

void Frame::storeVariable(int index, Operand* operand)
{
    map<int,Operand*>::iterator it = localVariables.find(index);
    
    if(it == localVariables.end())
    {
        localVariables.insert(make_pair(index, operand));
    }
    else
    {
        delete it -> second;
        it -> second = operand;
    }
}

Operand * Frame::loadVariable(int index)
{
    map<int,Operand*>::iterator it = localVariables.find(index);
    
    if(it != localVariables.end())
    {
        return it -> second;
    }
    else
    {
        return nullptr;
    }
}
