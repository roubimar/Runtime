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
}

int Frame::increasePc(int step)
{
    pc += step;
    return pc;
}
