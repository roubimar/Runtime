//
//  main.cpp
//  Run
//
//  Created by Marek Roubíček on 11.01.17.
//  Copyright © 2017 FIT ČVUT - RUN. All rights reserved.
//

#include <iostream>
#include <stack>

#include "./classFile.hpp"
#include "./classHeap.hpp"

using namespace std;

int main(int argc, char * argv[]){
    
    
    ClassHeap  * classHeap = new ClassHeap();
    
    
    try {
        classHeap -> getClass("test/MulNumbers");
    } catch(int e) {
        if(e == 21) cout << "Out of memory excefsdfdsfsdption" << endl;
        else if( e == 25) cout << "Class file load failed. Maybe wro22ng Class file name?" << endl;
        else cout << "Exception " << e << " occured" << endl;
        return 1;
    }
    
    cout << "DonexXxX: " << endl;
    return 0;

    
}
