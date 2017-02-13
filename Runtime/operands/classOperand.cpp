/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   classOperand.cpp
 * Author: daniel
 * 
 * Created on 26. ledna 2017, 14:41
 */

#include "classOperand.hpp"

ClassOperand::ClassOperand(ClassFile* classFile) 
{
    this -> val = classFile;
}

ClassOperand::~ClassOperand() {
}

Operand* ClassOperand::clone()
{
    return new ClassOperand(val);
}

