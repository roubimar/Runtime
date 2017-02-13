#include <map>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <limits>

#include "objectHeap.hpp"
#include "./operands/refOperand.hpp"

using namespace std;

ObjectHeap::ObjectHeap()
{
    heapSize = 1000;
    heap = new Operand*[heapSize];
    for (int i = 0; i < heapSize; i++)
    {
	heap[i] = nullptr;
    }
}

void ObjectHeap::setGarbageCollector(GarbageCollector* garbageCollector)
{
    this -> garbageCollector = garbageCollector;
}
ObjectHeap::~ObjectHeap()
{
}

u4 ObjectHeap::createObject(ClassFile* classFile)
{
        u4 objectSize	= classFile -> getObjectSize();
        
        u4 freeSpaceIndex = getFreeSpaceIndex(objectSize);
        if(freeSpaceIndex == numeric_limits<int>::max()) 
        {
            garbageCollector->clean();
            freeSpaceIndex = getFreeSpaceIndex(1);
        }
    
        if(freeSpaceIndex == numeric_limits<int>::max()){
            printf("NENI MISTO");
            // NENI MISTO
        }
        
        for (int i = freeSpaceIndex; i < freeSpaceIndex + objectSize; i++)
        {
            heap[i] = new RefOperand(numeric_limits<int>::max());
        }
          
        //TODO nasetovat do heapy
        //addHeapObjectRef(freeSpaceIndex, classFile);
}

/**
 * metoda, ktera vytvori operand na object heap
 * @return index, na ktery se operand nachazi
 */
u4 ObjectHeap::createOperand()
{
    u4 freeSpaceIndex = getFreeSpaceIndex(1);
    if(freeSpaceIndex == numeric_limits<int>::max()) 
    {
        garbageCollector->clean();
        freeSpaceIndex = getFreeSpaceIndex(1);
    }
    
    if(freeSpaceIndex == numeric_limits<int>::max())
    {
        printf("NENI MISTO");
        throw exception();
        // NENI MISTO
    }
    heap[freeSpaceIndex] = new RefOperand(0);
    return freeSpaceIndex;
}

u4 ObjectHeap::createStringObject(string val)
{
    return 5;
}

u4 ObjectHeap::getFreeSpaceIndex(u4 size)
{
    u4 index = 0;
    u4 counter = 0;
    
    while(index < heapSize)
    {
        if(counter == size)
        {
            return index - size;
        }
        if(heap[index] == nullptr)
        {
            counter++;
        } 
        else
        {
            counter = 0;
        }
        index++;
    }
    return numeric_limits<int>::max();
}