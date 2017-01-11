//
//  frame.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "operand.hpp"
#include "classFile.hpp"

#include <vector>
#include <stack>



using namespace std;

#ifndef frame_hpp
#define frame_hpp

#include <stdio.h>

class Frame
{
    public:
        // Proměnné
    
        // Seznam lokálních proměnných
        vector<Operand*> localVariables;
        // Stack pro manipulaci s operandy dle instrukcí
        stack<Operand*> operandStack;
        // Odkaz na class file
        ClassFile * classFile;
        // Informace o metodě daného frame, která se bude vyhledávat v dané classFile->methods
        string method_name;
        string method_description;
        // Program counter
        int pc;
    
        // Metody
        Frame(ClassFile * classFile, string method_name, string method_description);
        int increasePc(int step);
    
};

#endif /* frame_hpp */
