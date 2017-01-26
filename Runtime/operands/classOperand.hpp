#ifndef CLASSOPERAND_HPP
#define CLASSOPERAND_HPP

#include <stdio.h>
#include "operand.hpp"
using namespace std;

class ClassFile;
class ClassOperand  : public Operand
{
public:
    ClassFile * val;
    ClassOperand(ClassFile* classFile);
    ~ClassOperand();
private:

};

#endif /* CLASSOPERAND_HPP */

