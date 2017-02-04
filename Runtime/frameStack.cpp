//
//  FrameStack.cpp
//  Runtime
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include <iostream>
#include "frameStack.hpp"
#include "operands/intOperand.hpp"
#include "operands/stringOperand.hpp"
#include "operands/classOperand.hpp"

// Konsturktor
FrameStack::FrameStack(ClassFile * classFile, ObjectHeap *objectHeap, ClassHeap * classHeap)
{
    this->classFile = classFile;
    this->objectHeap = objectHeap;
    this->classHeap = classHeap;
    Frame * initFrame = new Frame(classFile, "main", "([Ljava/lang/String;)V", objectHeap);
    
    framesStack.push(initFrame);
    
}

FrameStack::~FrameStack(){
    while( !framesStack.empty())
    {
        framesStack.pop();
    }
}

// Vykonání nejvrchnějšího framu
void FrameStack::execute()
{
    actualFrame = framesStack.top();
    
    if(actualFrame -> classFile -> getMethod(actualFrame -> method_name, actualFrame -> method_description). access_flags & ACC_NATIVE )
    {
	executeNativeMethod();
	return;
    }
    
    method_info_w_code method = actualFrame -> classFile->getMethod(actualFrame->method_name, actualFrame->method_description);
    
    while(true)
    {
        // Vykonání jedné instrukce
        switch (method.code_attr->code[actualFrame->pc]) {
            case 0x00:
                actualFrame->increasePc(1);
                break;
            case 0x2a: //aload_0
                aload(0);
                break;
            case 0x2b: //aload_1
                aload(1);
            case 0x2c: //aload_2
                aload(2);
                break;
            case 0x2d: //aload_3
                aload(3);
                break;
            case 0x15: //iload
                iload(method.code_attr->code[actualFrame -> pc + 1 ]);
                actualFrame->increasePc(1);
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
            case 0x36:
                istore(method.code_attr->code[actualFrame -> pc + 1 ]);
                actualFrame->increasePc(1);
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
                ifeq(method.code_attr->code + actualFrame->pc);
                break;
            case 0x9a: //ifne
                ifne(method.code_attr->code + actualFrame->pc);
                break;
            case 0x9b: //iflt
                iflt(method.code_attr->code + actualFrame->pc);
                break;
            case 0x9c: //ifge
                ifge(method.code_attr->code + actualFrame->pc);
                break;
            case 0x9d: //ifgt
                ifgt(method.code_attr->code + actualFrame->pc);
                break;
            case 0x9e: //ifle
                ifle(method.code_attr->code + actualFrame->pc);
                break;
            case 0xb6: //invokevirtual
            case 0xb7: //invokespecial
                invoke(method.code_attr->code + actualFrame->pc, false);
                break;
            case 0xb8: //invokestatic
                invoke(method.code_attr->code + actualFrame->pc, true);
                break;
            case 0xbb: //new
                _new(method.code_attr->code + actualFrame->pc);
                break;
            case 0x12:
                ldc();
                break;
            case 0x9f: //if_icmpgt
                ifIcmpeq(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa0: //if_icmpgt
                ifIcmpne(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa1: //if_icmpgt
                ifIcmplt(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa2: //if_icmpgt
                ifIcmpge(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa3: //if_icmpgt
                ifIcmpgt(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa4: //if_icmpgt
                ifIcmple(method.code_attr->code + actualFrame->pc);
                break;
            case 0xa7: //goto
                _goto(method.code_attr->code + actualFrame->pc);
                break;
            case 0x84: //iinc
                iinc(method.code_attr->code + actualFrame->pc);
                break;
            case 0x59: //dup
                dup();
                break;
            case 0x57: //pop
                pop();
                break;
            case 0xb2: //getstatic
                getStatic();
                break;
            default:
                def();
                break;
                
        }
    }
}

void FrameStack::getStatic()
{
    actualFrame -> increasePc(3);
}
/**
 * nakopiruje na operand stack to co je na vrcholu
 */
void FrameStack::dup()
{
    actualFrame -> operandStack.push(actualFrame -> operandStack.top());
    actualFrame -> increasePc(1);
}

/**
 * pop z operand zasobniku
 */
void FrameStack::pop()
{
    actualFrame -> operandStack.pop();
    actualFrame -> increasePc(1);
}

/**
 * pricist k promenny z localVar na pozici p[1] cislo z p[2]
 * @param p ukazatel na aktualni funkci
 */
void FrameStack::iinc(u1 * p)
{
    IntOperand* operand = (IntOperand*)actualFrame -> loadVariable(p[1]);
    operand->val += p[2];
    actualFrame -> increasePc(3);
}

void FrameStack::_goto(u1 * p)
{
    u1 firstBranchByte;
    u1 secondBranchByte;

    firstBranchByte = (u1) p[1]; 
    secondBranchByte = (u1) p[2]; 
    short offset = (firstBranchByte << 8) | secondBranchByte;
    actualFrame->increasePc(offset);
}
void FrameStack::iadd()
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand * result = new IntOperand(firstOp -> val+ secondOp -> val);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::def()
{
    actualFrame->increasePc(1);
}

/**
 * nacteni Operandu z localVariable Framu do operandStacku Framu
 * @param index: pozice v local variables
 */
void FrameStack::aload(int index)
{
    actualFrame->operandStack.push(actualFrame->loadVariable(index));
    actualFrame->increasePc(1);
}

/**
* Nacitani intu z pole
*/
void FrameStack::iaload() 
{
    IntOperand* indexOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();

    IntOperand* refOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();

    //TODO dodelat az budou reference
    // potreba z heapu dostat pole a z nej vzit prvek podle indexu.
}

/**
 * nacteni Operandu z localVariable Framu do operandStacku Framu
 * @param index: pozice v local variables
 */
void FrameStack::iload(int index)
{
    actualFrame->operandStack.push(actualFrame->loadVariable(index));
    actualFrame->increasePc(1);
}

/**
 * Ulozeni Operandu z operandStacku do localVariables
 * @param index: pozice, na kterou se ma Operand ulozit
 */
void FrameStack::istore(int index)
{
    actualFrame->storeVariable(index, actualFrame->operandStack.top());
    actualFrame->operandStack.pop();
    actualFrame->increasePc(1);
}

void FrameStack::iconst(int constant)
{
    IntOperand * intOp = new IntOperand(constant);
    actualFrame->operandStack.push(intOp);
    actualFrame->increasePc(1);
}

void FrameStack::ret()
{
    framesStack.pop();
    delete actualFrame;
    actualFrame = framesStack.top();
}

void FrameStack::ireturn()
{
    IntOperand * tmp = (IntOperand*)actualFrame -> operandStack.top();
    framesStack.pop();
    framesStack.top() -> operandStack.push(tmp);
    delete actualFrame;
    actualFrame = framesStack.top();
}


// deleni integeru
void FrameStack::idiv()
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand * result = new IntOperand(firstOp -> val / secondOp -> val);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

// negace integeru
void FrameStack::ineg()
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand * result = new IntOperand(firstOp -> val * -1);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

// nasobeni integeru
void FrameStack::imul()
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand * result = new IntOperand(firstOp -> val * secondOp -> val);
    actualFrame->operandStack.push(result);
    actualFrame->increasePc(1);
}

void FrameStack::ifConditionIncreasePc(bool result, u1 * p)
{
    u1 firstBranchByte;
    u1 secondBranchByte;
    if(result) 
    {
        firstBranchByte = (u1) p[1]; 
        secondBranchByte = (u1) p[2]; 
        short offset = (firstBranchByte << 8) | secondBranchByte;
        actualFrame->increasePc(offset);
    } 
    else 
    {
        actualFrame->increasePc(3);
    }
}

// porovnani jestli je integer == 0
void FrameStack::ifeq(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val == 0;

    ifConditionIncreasePc(result, p);
}

// porovnani jestli se integer != 0
void FrameStack::ifne(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val != 0;

    ifConditionIncreasePc(result, p);
}

// porovnani jestli je integer < 0
void FrameStack::iflt(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val < 0;

    ifConditionIncreasePc(result, p);
}

// porovnani jestli je integer >= 0
void FrameStack::ifge(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val >= 0;

    ifConditionIncreasePc(result, p);
}

// porovnani jestli je integer > 0
void FrameStack::ifgt(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val > 0;

    ifConditionIncreasePc(result, p);
}

// porovnani jestli je integer <= 0
void FrameStack::ifle(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();

    bool result = firstOp -> val <= 0;

    ifConditionIncreasePc(result, p);
}

// porovnani dvou integeru jestli je prvni >= druhy
void FrameStack::ifIcmpgt(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val < secondOp -> val, p);
}


// porovnani dvou integeru jestli se prvni = druhy
void FrameStack::ifIcmpeq(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val == secondOp -> val, p);
}


// porovnani dvou integeru jestli se prvni mensi != druhy
void FrameStack::ifIcmpne(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val != secondOp -> val, p);
}


// porovnani dvou integeru jestli je prvni mensi <= druhy
void FrameStack::ifIcmplt(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val > secondOp -> val, p);
}


// porovnani dvou integeru jestli je prvni mensi > druhy
void FrameStack::ifIcmple(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val <= secondOp -> val, p);
}


// porovnani dvou integeru jestli je prvni mensi > druhy
void FrameStack::ifIcmpge(u1 * p)
{
    IntOperand* firstOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    IntOperand* secondOp = (IntOperand*)actualFrame->operandStack.top();
    actualFrame->operandStack.pop();
    
    ifConditionIncreasePc(firstOp -> val <= secondOp -> val, p);
}

// zavolani metody
void FrameStack::invoke(u1 * p, bool lessParams)
{
    // index metody v konstant poolu
    u2 methodRef = getu2(&p[1]);

    // z konstant poolu vybereme pozici na ktere  je metoda
    u1 * methodPosition = (u1*)actualFrame -> classFile -> constant_pool[methodRef];

    u2 classIndex = getu2(methodPosition + 1);
    u1 * classInfo = (u1*) actualFrame -> classFile -> constant_pool[classIndex];
    u2 nameIndexClass = getu2(classInfo + 1);
    string className;
    actualFrame -> classFile -> getAttrName(nameIndexClass, className);
    
    // na 4. pozici se nachazi name and type index, ktery ukazuje znovu do konstant poolu na jinou pozici, ktera obsahuje indexy na nazvem a navratovou hodnotou metody
    u2 nameAndTypeIndex = getu2(methodPosition + 3);

    // ukazatel na strukturu, ktera obsahuje indexy na nazev a navratovou hodnotu metody
    u1 *nameAndTypeInfo = (u1*)actualFrame -> classFile -> constant_pool[nameAndTypeIndex];

    // ziskani samotnych indexu zanvu a navratovy hodnoty
    u2 nameIndexMethod = getu2(nameAndTypeInfo + 1);
    u2 descriptorIndex = getu2(nameAndTypeInfo + 3);

    // z indexu ziskame nazev a popis metody (navratovy hodnoty)
    string methodName, methodDescription;
    actualFrame -> classFile -> getAttrName(nameIndexMethod, methodName);
    actualFrame -> classFile -> getAttrName(descriptorIndex, methodDescription);
   
    int numberOfparams = (short)getNumberOfMethodParams(methodDescription);

    ClassFile* newClassFile = classHeap -> getClass("test/" + className, objectHeap);
    // vytvoreni noveho Framu a pridani na zasobnik
    Frame * invokedFrame = new Frame(newClassFile, methodName, methodDescription, objectHeap);
    
    if(invokedFrame -> classFile -> getMethod(invokedFrame -> method_name, invokedFrame -> method_description). access_flags & ACC_NATIVE )
    {
	//executeNativeMethod();
	//return;
    }
    
    if(lessParams || invokedFrame -> classFile -> getMethod(invokedFrame -> method_name, invokedFrame -> method_description). access_flags & ACC_NATIVE)
    {
        numberOfparams--;
    }
    // pokud ma metoda nejaky porametry, pridame je na zasobnik jejiho framu
    for (int i = numberOfparams; i >= 0; i--)
    {
        Operand* o = actualFrame->operandStack.top();
        actualFrame->operandStack.pop();
        invokedFrame->storeVariable(i, o);
        
    }

    framesStack.push(invokedFrame);

    execute();
    
    actualFrame->increasePc(1);
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


u4 FrameStack::_new(u1 * p)
{
        // index metody v konstant poolu
        u2 methodRef = getu2(&p[1]);
        
        // z konstant poolu vybereme pozici na ktere  je metoda
        u1 * methodPosition = (u1*)actualFrame -> classFile -> constant_pool[methodRef];

	u2 classNameIndex = getu2(methodPosition + 1);

	string className;
	actualFrame -> classFile -> getAttrName(classNameIndex, className);

        ClassFile* newClassFile = classHeap -> getClass("test/" + className, objectHeap);
        ClassOperand* classOperand = new ClassOperand(newClassFile);
        
        actualFrame->operandStack.push(classOperand);
        
        actualFrame->increasePc(3);
}

void FrameStack::ldc()
{
        //TODO
//Operand * valueOp = new RefOperand( loadConstant());
				
				//frame -> pushOperand(valueOp);
				//frame -> movePc(2);
}

int FrameStack::loadConstant(u1 * p)
{
	u1 constPoolIndex = getu1(&p[actualFrame -> pc + 1]);

	u1 * constPoolInfo = (u1*)actualFrame -> classFile -> constant_pool[constPoolIndex];

	switch(constPoolInfo[0])
	{
		case CONSTANT_Integer:

			break;
		case CONSTANT_Float:

			break;
		case CONSTANT_String:
			u2 constPoolUtfIndex = getu2(constPoolInfo + 1);
			string stringValue;
			actualFrame -> classFile -> getAttrName(constPoolUtfIndex, stringValue);
			return objectHeap -> createStringObject(stringValue);
	}
	return -1;
}


void FrameStack::executeNativeMethod()
{
    string className = actualFrame -> classFile -> getName();
    string methodName = actualFrame -> method_name;
    string methodDescription = actualFrame -> method_description;
        
    string methodSignature = className + "." + methodName + ":" + methodDescription;
	 

    if(methodSignature.compare("java/io/PrintStream.print:(Ljava/lang/String;)V") == 0) 
    {
    	printString();
    } 
    else
    {
        if(methodSignature.compare("java/io/PrintStream.print:(I)V") == 0) 
        {
            printInt();
	} 
        else 
        {
            if(methodSignature.compare("test/our/objects/StdInputReader.readString:()Ljava/lang/String;") == 0) 
            {
		readString();
            } 
        }
    }
}

void FrameStack::printString()
{
    StringOperand* operand = (StringOperand*) actualFrame -> loadVariable(0);
    cout << operand -> val << endl;
    framesStack.pop();
    actualFrame = framesStack.top();
}


void FrameStack::printInt()
{
    IntOperand* operand = (IntOperand*) actualFrame -> loadVariable(0);
    cout << operand -> val << endl;
    framesStack.pop();
    actualFrame = framesStack.top();
}


void FrameStack::readString()
{
    string input;
    cin >> input;
    StringOperand* operand = new StringOperand(input);
    
    framesStack.pop();
    framesStack.top() -> operandStack.push(operand);
    actualFrame = framesStack.top();
}





   
