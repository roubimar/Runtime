//
//  frame.hpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "operands/operand.hpp"
#include "classFile.hpp"

#include <map>
#include <stack>



using namespace std;
class ObjectHeap;
#ifndef frame_hpp
#define frame_hpp

#include <stdio.h>

class Frame
{
    public:
        // Proměnné
    
        // Seznam lokálních proměnných
        int * localVariables;
        // Stack pro manipulaci s operandy dle instrukcí
        stack<Operand*> operandStack;
        // Odkaz na class file
        ClassFile * classFile;
        // Informace o metodě daného frame, která se bude vyhledávat v dané classFile->methods
        string method_name;
        string method_description;
        // Program counter
        int pc;
        
        int maxLocals;
        
        ObjectHeap * objectHeap;
        // Metody
        Frame(ClassFile * classFile, string method_name, string method_description, ObjectHeap* objectHeap);
        ~Frame();
        int increasePc(int step);
    
        void storeVariable(int index, Operand* operand);
        Operand * loadVariable(int index);
        void initLocalVar();

    
};

#endif /* frame_hpp */
