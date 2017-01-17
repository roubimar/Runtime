//
//  Operand.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#ifndef stringOperand_hpp
#define sringOperand_hpp
#include <string>
#include "operand.hpp"


using namespace std;

class StringOperand : public Operand
{
public:
    string val;
    
    StringOperand(string value);
    ~StringOperand();
};

#endif /* operand_hpp */
