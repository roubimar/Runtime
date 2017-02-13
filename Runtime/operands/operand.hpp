#ifndef operand_hpp
#define operand_hpp

class Operand{
public:
    bool mark;
    Operand();
    virtual ~Operand();
    virtual Operand* clone();
};

#endif /* operand_hpp */
