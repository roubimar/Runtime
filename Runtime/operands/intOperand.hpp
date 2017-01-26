//
//  Operand.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#ifndef intOperand_hpp
#define intOperand_hpp

#include <stdio.h>
#include "operand.hpp"
using namespace std;


class IntOperand : public Operand
{
public:
    int val;
    
    IntOperand(int value);
    ~IntOperand();
};

#endif /* operand_hpp */
