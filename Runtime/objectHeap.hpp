#ifndef objectHeap_hpp
#define objectHeap_hpp

#include "operands/operand.hpp"
#include "classFile.hpp"
#include "GarbageCollector.hpp"

using namespace std;



#include <stdio.h>

class ObjectHeap
{
    public:
        // Proměnné
        u4 nextObjectID;
        Operand ** heap;
        int heapSize;
        GarbageCollector* garbageCollector;
        // Metody
        ObjectHeap();
        ~ObjectHeap();
        void setGarbageCollector(GarbageCollector* garbageCollector);
        u4 createObject(ClassFile* classFile);
        u4 createOperand();
        u4 createStringObject(string val);
        u4 getFreeSpaceIndex(u4 size);

    
};

#endif /* objectHeap_hpp */
