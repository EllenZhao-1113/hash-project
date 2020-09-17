#Ellen Zhao
#Makefile for Proj2
#Project 2
#Spring 2019
#

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra -O3
LDFALGS  = -g3

gerp: DirNode.o FSTree.o HashNode.o HashLinkedList.o Hash.o main.cpp
        ${CXX} ${LDFLAGS} -o gerp DirNode.o FSTree.o HashNode.o HashLinkedList.o Hash.o main.cpp
UnitTests:DirNode.o FSTree.o UnitTesting.o HashLinkedList.o Hash.o
        ${CXX} ${LDFLAGS} -o UnitTests DirNode.o FSTree.o UnitTesting.o HashLinkedList.o Hash.o

DirNode.o: DirNode.h DirNode.cpp
FSTree.o: FSTree.h FSTree.cpp
Hash.o: Hash.h Hash.cpp
HashNode.o: HashNode.h
HashLinkedList.o: HashLinkedList.h HashLinkedList.cpp
UnitTesting.o: UnitTesting.cpp

clean: rm -rf gerp *.o* *.dSYM
