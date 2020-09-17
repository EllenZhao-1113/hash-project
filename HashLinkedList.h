//Ellen Zhao
//HashLinkedList.h
//Project 2
//COMP15
//Spring 2019
//Interface of HashLinkedList
//

#ifndef HASHLINKEDLIST_H
#define HASHLINKEDLIST_H

#include <vector>
#include <string>
#include <iostream>
#include "HashNode.h"

class HashLinkedList {
    public:
        //constructor
        HashLinkedList();
        HashLinkedList(HashNode * other);
        //destructor
        ~HashLinkedList();
        //copy constructor
        HashLinkedList(const HashLinkedList&other);
        // assignment overload. Will seg fault if copied onto itself.
        HashLinkedList& operator=(const HashLinkedList &other);

        //inserts a HashNode into list
        HashNode * insert(std::string name);
        void deleteList();                    //deletes the list
        HashNode* getRoot();                  //returns root
        HashNode* search(std::string word);   //checks if element is in list
        int numElem();                        //number of elements in list

    private:
        HashNode * root;                      //root of list
        string outFile;                       //output file
};

#endif
