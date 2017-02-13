#include "classHeap.hpp"
#include "classFile.hpp"

using namespace std;


ClassFile * ClassHeap::getClass(string className, ObjectHeap * objectHeap)
{
	map<string, ClassFile *>::iterator it;
	it = classHeap.find(className);
	if(it == classHeap.end())
	{
            string classFileName = className +".class";
            ClassFile * insertClass = new ClassFile(classFileName, this, objectHeap);
            classHeap . insert( pair<string, ClassFile *>(className, insertClass ) );
	}
	return classHeap[className];
}

ClassHeap::~ClassHeap()
{
	classHeap.clear();
}
