//
//  frame.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "operand.hpp"

#include <vector>



using namespace std;

#ifndef frame_hpp
#define frame_hpp

#include <stdio.h>

class Frame
{
    vector<Operand*> localVariables;
};

#endif /* frame_hpp */
