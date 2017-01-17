#ifndef CLASSHEAP_HPP_
#define CLASSHEAP_HPP_

#include <map>
#include <cstring>


using namespace std;
class ClassFile;
class ObjectHeap;

class ClassHeap{
	private:
        map<string, ClassFile *> classHeap;
	public:
                
		ClassFile * getClass(string className, ObjectHeap* objectHeap);
		~ClassHeap();
};

#endif /* CLASSHEAP_HPP_ */
