#ifndef CLASSHEAP_HPP_
#define CLASSHEAP_HPP_

#include <map>
#include <cstring>

#include "classLoader.hpp"
#include "classFile.hpp"

using namespace std;

class ClassHeap{
	private:
    map<string, ClassFile *> classHeap;
		ClassLoader 					 classLoader;
	public:
		ClassFile * getClass(string className);
};

#endif /* CLASSHEAP_HPP_ */
