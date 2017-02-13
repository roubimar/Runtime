//
//  Operand.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "refOperand.hpp"


RefOperand::RefOperand(int index)
{
    this -> index = index;
}

RefOperand::~RefOperand()
{
}

Operand* RefOperand::clone()
{
    return new RefOperand(index);
}


