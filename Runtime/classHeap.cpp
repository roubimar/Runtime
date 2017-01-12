
#include "./classHeap.hpp"
#include "./classFile.hpp"

using namespace std;

ClassFile * ClassHeap::getClass(string className)
{
	map<string, ClassFile *>::iterator it;
	it = classHeap.find(className);
	if(it == classHeap.end())
	{
		ClassFile * insertClass = new ClassFile("test/" + className +".class", this);
		classHeap . insert( pair<string, ClassFile *>(insertClass -> getName(), insertClass ) );
	}
	return classHeap["test/" + className];
}

ClassHeap::~ClassHeap()
{
	classHeap.clear();
}
