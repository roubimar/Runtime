
#include "./classHeap.hpp"
#include "./classLoader.hpp"
#include "./classFile.hpp"

using namespace std;

ClassFile * ClassHeap::getClass(string className)
{
	map<string, ClassFile *>::iterator it;
	it = classHeap.find(className);
	if(it == classHeap.end())
	{
		ClassFile * insertClass = classLoader.loadClass(className, this);
		classHeap . insert( pair<string, ClassFile *>(insertClass -> getName(), insertClass ) );
	}
	return classHeap[className];
}
