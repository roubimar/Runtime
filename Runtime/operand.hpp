//
//  Operand.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#ifndef operand_hpp
#define operand_hpp

#include <stdio.h>


class Operand{
public:
    int value;
    
    Operand(int value);
    ~Operand();
};

#endif /* operand_hpp */
