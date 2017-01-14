//
//  FrameStack.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include "frameStack.hpp"


// Konsturktor
FrameStack::FrameStack(ClassFile * classFile)
{
    this->classFile = classFile;
    Frame * initFrame = new Frame(classFile, "main", "([Ljava/lang/String;)V");
    
    framesStack.push(initFrame);
    
}

FrameStack::~FrameStack(){
    while( !framesStack.empty())
    {
        framesStack.pop();
    }
    delete classFile;
}

// Vykonání nejvrchnějšího framu
void FrameStack::execute()
{
    actualFrame = framesStack.top();
    
    method_info_w_code method = classFile->getMethod(actualFrame->method_name, actualFrame->method_description);
    
    // Code pointer
    u1 * p = method.code_attr->code;
    while(true)
    {
        // Vykonání jedné instrukce
        switch (p[actualFrame->pc]) {
            case 0x00:
                
                break;
            case 0x15: //iload
                iload(p[actualFrame -> pc + 1 ]);
                break;
            case 0x1a: //iload_0
                iload(0);
                break;
            case 0x1b: //iload_1
                iload(1);
                break;
            case 0x1c: //iload_2
                iload(2);
                break;
            case 0x1d: //iload_3
                iload(2);
                break;
            case 0x3b: //istore_0
                istore(0);
                break;
            case 0x3c: //istore_1
                istore(1);
                break;
            case 0x3d: //istore_2
                istore(2);
                break;
            case 0x3e: //istore_3
                istore(3);
                break;
            case 0x02: //iconst_m1
                iconst(-1);
                break;
            case 0x03: //iconst_0
                iconst(0);
                break;
            case 0x04: //iconst_1
                iconst(1);
                break;
            case 0x05: //iconst_2
                iconst(2);
                break;
            case 0x06: //iconst_3
                iconst(3);
                break;
            case 0x07: //iconst_4
                iconst(4);
                break;
            case 0x08: //iconst_5
                iconst(5);
                break;
            case 0x60: //iadd
                iadd();
                break;
            case 0xb1: //return
                ret();
                return;
            case 0x74: //ineg
                ineg();
                return;
            case 0x6c: //idiv
                idiv();
                return;
            case 0x68: //multiplication
                imul();
                return;
            case 0xac: //ireturn
                ireturn();
                return;
            case 0x2e: //iaload
                iaload();
                break;
            case 0x99: //ifeq
                ifeq(p);
                break;
            case 0x9a: //ifne
                ifne(p);
                break;
            case 0x9b: //iflt
                iflt(p);
                break;
            case 0x9c: //ifge
                ifge(p);
                break;
            case 0x9d: //ifgt
                ifgt(p);
                break;
            case 0x9e: //ifle
                ifle(p);
                break;
            case 0xb8:
                invokestatic(p);
                break;
            default:
                def();
                break;
                
        }
    }
}

void FrameStack::iadd()
{
    Operand* firstOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand* secondOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp -> value + secondOp -> value);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::def()
{
    actualFrame->increasePc(1);
}

/**
* Nacitani intu z pole
*/
void FrameStack::iaload() 
{
    Operand* indexOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();

    Operand* refOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();

    //TODO dodelat az budou reference
    // potreba z heapu dostat pole a z nej vzit prvek podle indexu.
}
void FrameStack::iload(int index)
{
    actualFrame->operandStack.push(actualFrame->loadVariable(index));
    actualFrame->increasePc(1);
}

void FrameStack::istore(int index)
{
    actualFrame->storeVariable(index, actualFrame->operandStack.top());
    actualFrame->operandStack.pop();
    actualFrame->increasePc(1);
}

void FrameStack::iconst(int constant)
{
    Operand * intOp = new Operand(constant);
    actualFrame->operandStack.push(intOp);
    actualFrame->increasePc(1);
}

void FrameStack::ret()
{
    framesStack.pop();
    delete actualFrame;
}

void FrameStack::ireturn()
{
    Operand * tmp = actualFrame -> operandStack.top();
    framesStack.pop();
    framesStack.top() -> operandStack.push(tmp);
}


void FrameStack::idiv()
{
    Operand* firstOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand* secondOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp -> value / secondOp -> value);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}


void FrameStack::ineg()
{
    Operand* firstOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp -> value * -1);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::imul()
{
    Operand* firstOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand* secondOp = actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    Operand * result = new Operand(firstOp -> value * secondOp -> value);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::ifConditionIncreasePc(bool result, u1 * p)
{
    u1 firstBranchByte;
    u1 secondBranchByte;
    if(result) 
    {
        firstBranchByte = (u1) p[actualFrame -> pc + 1]; 
        secondBranchByte = (u1) p[actualFrame -> pc + 2]; 
        short offset = (firstBranchByte << 8) | secondBranchByte;
        actualFrame->increasePc(offset);
    } 
    else 
    {
        actualFrame->increasePc(3);
    }
}

void FrameStack::ifeq(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value == 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::ifne(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value != 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::iflt(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value < 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::ifge(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value >= 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::ifgt(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value > 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::ifle(u1 * p)
{
    Operand* firstOp = actualFrame->operandStack.top();

    bool result = firstOp -> value <= 0;

    ifConditionIncreasePc(result, p);
}

void FrameStack::invokestatic(u1 * p)
{
    // index metody v konstant poolu
    u2 methodRef = getu2(&p[actualFrame -> pc + 1]);

    // z konstant poolu vybereme pozici na ktere  je metoda
    u1 * methodPosition = (u1*)actualFrame -> classFile -> constant_pool[methodRef];

    // na 4. pozici se nachazi name and type index, ktery ukazuje znovu do konstant poolu na jinou pozici, ktera obsahuje indexy na nazvem a navratovou hodnotou metody
    u2 nameAndTypeIndex = getu2(methodPosition + 3);

    // ukazatel n astrukturu, ktera obsahuje indexy na nazev a navratovou hodnotu metody
    u1 *nameAndTypeInfo = (u1*)actualFrame -> classFile -> constant_pool[nameAndTypeIndex];

    // ziskani samotnych indexu zanvu a navratovy hodnoty
    u2 nameIndexMethod = getu2(nameAndTypeInfo + 1);
    u2 descriptorIndex = getu2(nameAndTypeInfo + 3);

    // z indexu ziskame nazev a popis metody (navratovy hodnoty)
    string methodName, methodDescription;
    actualFrame -> classFile -> getAttrName(nameIndexMethod, methodName);
    actualFrame -> classFile -> getAttrName(descriptorIndex, methodDescription);
   
    int numberOfparams = (short)getNumberOfMethodParams(methodDescription);

    // vytvoreni noveho Framu a pridani na zasobnik
    Frame * invokedFrame = new Frame(classFile, methodName, methodDescription);

    numberOfparams--;
    // pokud ma metoda nejaky porametry, pridame je na zasobnik jejiho framu
    for (int i = numberOfparams; i >= 0; i--)
    {
        Operand* o = actualFrame->operandStack.top();
        actualFrame->operandStack.pop();
        invokedFrame -> localVariables.insert(make_pair(i, o));
        
    }

    framesStack.push(invokedFrame);

    execute();
}

u2 FrameStack::getNumberOfMethodParams(string p_description)
{
	u2 	count = 0;
	int length = p_description.size();

	for (int i = 1; i < length; i++)
	{
		if(p_description[i] == '[')
		{
			continue;
		}
		if(p_description[i] == 'L')
		{
			while(p_description[i] != ';')
			{
				i++;
			}
		}
		if(p_description[i] == ')')
		{
			break;
		}
		count++;
	}
	return count;
}




   
