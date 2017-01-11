
#include <iostream>

#include "./classLoader.hpp"

using namespace std;

ClassFile * ClassLoader::loadClass(string className, ClassHeap * classHeap)
{
	ClassFile * classfile = new ClassFile(classHeap);
	cout << "Loading class: " << className << endl;
	classfile -> loadClass(className + ".class");
	cout << "Loaded: " << classfile -> getName() << endl;
	return classfile;  
}
