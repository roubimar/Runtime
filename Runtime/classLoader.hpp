#ifndef CLASSLOADER_HPP_
#define CLASSLOADER_HPP_

#include "classFile.hpp"


using namespace std;

class ClassLoader{
	private:

	public:
		ClassFile * loadClass(string className, ClassHeap * classHeap);
};

#endif /* CLASSLOADER_HPP_ */
