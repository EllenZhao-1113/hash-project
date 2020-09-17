File Edit Options Buffers Tools C++ Help
//Ellen Zhao
//main.cpp
//Project 2
//COMP15
//Spring 2019
//runs program
//

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include "HashNode.h"
#include "HashLinkedList.h"
#include "FSTree.h"
#include "DirNode.h"
#include "Hash.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 3) {
        Hash map;
        string wholeFile = argv[1];
        string outPut = argv[2];
        map.setOutfile(outPut);
        map.buildTree(wholeFile);
        map.query();
        cout << map.getNumKeys() << " " << map.getSize() << endl;
    }
    else {
      cout << "usage: ./gerp input_directory output_directory" << endl;
    }
    return 0;
}
