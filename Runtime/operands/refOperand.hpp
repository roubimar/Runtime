#ifndef refOperand_hpp
#define refOperand_hpp

#include "operand.hpp"


using namespace std;

class RefOperand : public Operand
{
public:
    int index;
    
    RefOperand(int index);
    ~RefOperand();
    Operand* clone();
};

#endif 
