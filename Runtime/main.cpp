//
//  main.cpp
//  Runtime
//
//  Created by Marek Roubíček on 10.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include <iostream>

using namespace std;
class Frame {
    
public:
    Frame() {};
    int a;
};

int main(int argc, const char * argv[]) {
    
    std::cout << "Hello, World!\n";
    
    
    Frame* f = new Frame();
    f->a = 10;
    
    cout << f->a;
    
    return 0;
}
