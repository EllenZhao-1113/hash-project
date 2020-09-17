//Ellen Zhao
//HashLinkedList.cpp
//Project 2
//COMP15
//Spring 2019
//Implementation of HashLinkedList
//

#include <iostream>
#include <fstream>
#include <vector>
#include "HashLinkedList.h"
#include "HashNode.h"

using namespace std;

//constuctor
HashLinkedList::HashLinkedList() {
    root = NULL;
    outFile = "";
}

//pconstructor that sets root
HashLinkedList::HashLinkedList(HashNode * other) {
    root = other;
    outFile = "";
}

//destructor---deletes all elements of linked list
HashLinkedList::~HashLinkedList(){
    deleteList();
}

//copy constructor
HashLinkedList::HashLinkedList(const HashLinkedList &other){
    if (other.root == NULL) {
        root = NULL;
    }
    else {
        root = new HashNode;
        root->word = other.root->word;
        int size = other.root->where.size();
        for (int i = 0; i < size; i++) {
          root->where.push_back(other.root->where[i]);
        }
        root->next = NULL;
        HashNode * temp = root;
        HashNode * orig = other.root;
        while (orig->next != NULL) {
          temp->next = new HashNode;
          temp->next->word = orig->next->word;
          int count = orig->next->where.size();
          for (int i = 0; i < count; i++) {
            temp->next->where.push_back(orig->next->where[i]);
          }
          temp->next->next = NULL;
          orig = orig->next;
          temp = temp->next;
        }
    }
}

// assignment overload. Will seg fault if copied onto itself.
HashLinkedList &HashLinkedList::operator=(const HashLinkedList &other){
    if (this != &other) {

      if (other.root == NULL) {
        root = NULL;
      }
      else {
        root = new HashNode;
        root->word = other.root->word;
        int size = other.root->where.size();
        for (int i = 0; i < size; i++) {
          root->where.push_back(other.root->where[i]);
        }
        root->next = NULL;
        HashNode * temp = root;
        HashNode * orig = other.root;
        while (orig->next != NULL) {
          temp->next = new HashNode;
          temp->next->word = orig->next->word;
          int count = orig->next->where.size();
          for (int i = 0; i < count; i++) {
              temp->next->where.push_back(orig->next->where[i]);
          }
          temp->next->next = NULL;
          orig = orig->next;
          temp = temp->next;
        }
      }
    }
    return *this;
}

//Function: inserts elementt into list
//Input: string (HashNode word)
//Returns: HashNode pointer (new hashNode made)
//Does: creats the node and adds it to the end of the front
// of the list
HashNode * HashLinkedList:: insert(string name){
    HashNode * newNode = new HashNode;
    newNode->word = name;
    newNode->next = root;
    root = newNode;
    return newNode;
}

//Function: deletes the whole list
//Input: nothing
//Returns: none
//Does: deletes list starting from from first
// elem to the last
void HashLinkedList::deleteList() {
    HashNode * deleteNode = NULL;
    HashNode * temp = root;
    while (temp!=NULL) {
        deleteNode = temp;
        temp = temp->next;
        deleteNode->next = NULL;
        delete deleteNode;
    }
    root = NULL;
}

//Function: returns the root
HashNode* HashLinkedList::getRoot(){
    return root;
}

//Function: finds elem
//Input: string (word of the hashNode)
//Returns: HashNode pointer
//Does: finds the hashNode that holds that string
// and returns it
HashNode* HashLinkedList::search(string word){
    HashNode * temp = root;
    while (temp != NULL) {
        if (temp->word == word) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//Funciton: finds number of elems in list
//Input: none
//Returns: integer
//Does: iterates through list and counts
int HashLinkedList::numElem() {
    int count = 0;
    HashNode * temp = root;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
