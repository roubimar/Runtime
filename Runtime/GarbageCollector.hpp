/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GarbageCollector.hpp
 * Author: daniel
 *
 * Created on 26. ledna 2017, 9:11
 */

#ifndef GARBAGECOLLECTOR_HPP
#define GARBAGECOLLECTOR_HPP

#include "frameStack.hpp"
#include <map>

class FrameStack;
class ObjectHeap;

class GarbageCollector {
public:
    ObjectHeap * objectHeap;
    FrameStack * frameStack;
    ClassHeap  * classHeap;
    
    GarbageCollector(ObjectHeap* objectHeap, FrameStack* frameStack, ClassHeap  * classHeap);
    virtual ~GarbageCollector();
    void mark();
    void clean();
    void sweep();
    void markFrame();
    void markClass(ClassFile* classFile);
private:

};

#endif /* GARBAGECOLLECTOR_HPP */

