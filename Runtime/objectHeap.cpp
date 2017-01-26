#include <map>
#include <stdio.h>
#include <string.h>

#include "objectHeap.hpp"
#include "refOperand.hpp"

ObjectHeap::ObjectHeap()
{
    heap = new Operand*[heapSize];
    for (int i = 0; i < heapSize; i++)
    {
	heap[i] = nullptr;
    }
    
    heapSize = 100;
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
        if(freeSpaceIndex == -1) 
        {
            garbageCollector->clean();
            freeSpaceIndex = getFreeSpaceIndex(1);
        }
    
        if(freeSpaceIndex == -1){
            // NENI MISTO
        }
        
        for (int i = freeSpaceIndex; i < freeSpaceIndex + objectSize; i++)
        {
            heap[i] = new RefOperand(-1);
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
    if(freeSpaceIndex == -1) 
    {
        garbageCollector->clean();
        freeSpaceIndex = getFreeSpaceIndex(1);
    }
    
    if(freeSpaceIndex == -1){
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
    return -1;
}