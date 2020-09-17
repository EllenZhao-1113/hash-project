//Ellen Zhao
//Project 2
//COMP15
//Spring 2019
//traverses file system and prints
//

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <vector>
#include <exception>
#include "FSTree.h"
#include "DirNode.h"
using namespace std;

//prints all sub directories and files
void printFiles(DirNode *node, string file);

//takes the input and makes a tree
// and calls printFile to print
int main(int argc, char* argv[]) {
    if (argc == 2) {
        string wholeFile = argv[1];
        cout << wholeFile << endl;
        FSTree tree(wholeFile);
        DirNode * root = tree.getRoot();
        printFiles(root, argv[1]);
    }
    return 0;
}

//Function: print all subDirectories and files
//Input: DirNode pointer and a string
//Returns: nothing
//Does:recursively gors throgh FSTree and
// prints files and subdirectories
void printFiles(DirNode * node, string file) {
    string mod = file;
    int subDirs = node->numSubDirs();
    int files = node->numFiles();
    if (subDirs == 0 and files == 0) {
           mod = file;
    }
    for (int i = 0; i < subDirs; i++) {
        DirNode * temp =  node->getSubDir(i);
        mod =  mod + "/" + temp->getName();
        cout << mod << endl;
        printFiles(temp, file);
    }
    for (int j = 0; j < files; j++) {
        string fname = node->getFile(j);
        cout << mod << "/" << fname << endl;
    }
}
