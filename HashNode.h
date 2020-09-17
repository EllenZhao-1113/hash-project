//Ellen Zhao
//Project 2
//COMP15
//Spring 2019
//struct HashNode

#ifndef HASHNODE_H
#define HASHNODE_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct HashNode {
    std::string word;             //word  (what query wants to find)
    std::vector<int> where;       //vector on integers that hold the index
                                  //where the word appears in the allLines vector
    HashNode * next;              //next hashnode in the lsit
};
#endif

