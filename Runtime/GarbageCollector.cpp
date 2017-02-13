/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GarbageCollector.cpp
 * Author: daniel
 * 
 * Created on 26. ledna 2017, 9:11
 */
#include <iostream>
#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector(ObjectHeap* objectHeap, FrameStack* frameStack, ClassHeap  * classHeap) {
    this -> objectHeap = objectHeap;
    this -> frameStack = frameStack;
    this -> classHeap = classHeap;
}

GarbageCollector::~GarbageCollector() {
}

void GarbageCollector::markFrame(){
    if(frameStack -> framesStack.empty()){
        return;
    }
    Frame* tmpFrame = frameStack -> framesStack.top();
    frameStack -> framesStack.pop();
    int * frameLocalVar = tmpFrame -> localVariables;
    for(int i = 0; i < (sizeof(frameLocalVar)/sizeof(*frameLocalVar)); i++)
    {
        objectHeap -> heap[frameLocalVar[i]] -> mark = true;
    }
    markFrame();
    frameStack -> framesStack.push(tmpFrame);
}

void GarbageCollector::markClass(ClassFile* classFile)
{
    int * instanceVar = classFile -> instanceVar;
    for(int i = 0; i < (sizeof(instanceVar)/sizeof(*instanceVar)); i++)
    {
        objectHeap -> heap[instanceVar[i]] -> mark = true;
    }
}

void GarbageCollector::mark() 
{
    for (int i = 0; i < objectHeap -> heapSize; i++)
    {
        if(objectHeap->heap[i] != nullptr && objectHeap->heap[i] != NULL)
        {
            objectHeap->heap[i] -> mark = false;
        }
    }
    markFrame();
    
    for(map<string, ClassFile *>::iterator iter = classHeap -> classHeap.begin(); iter != classHeap -> classHeap.end(); iter++)
    {
        markClass(iter -> second);
    }
}

void GarbageCollector::sweep() 
{
    int counter = 0;
    for(int i = 0; i < objectHeap -> heapSize; i++)
    {
        if(objectHeap->heap[i] != nullptr && objectHeap->heap[i] != NULL && !objectHeap->heap[i]->mark)
        {
            delete objectHeap->heap[i];
            objectHeap->heap[i] = nullptr;
            counter++;
        } 
    }
    cout << "Uvolneno: " << counter << endl;
}

void GarbageCollector::clean()
{
    mark();
    sweep();
}


