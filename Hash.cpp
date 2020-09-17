//Ellen Zhao
//Hash.cpp
//Project 2
//COMP15
//Spring 2019
//Implementation of Hash
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

//constructor
Hash::Hash(){
    numKeys = 0;
    sizeArray = 100000;
    outFile = "";
    hashArray = new HashLinkedList[100000];
    for (int i=0; i < sizeArray; i++) {
        hashArray[i] = NULL;
    }
}

//deconstructor
Hash::~Hash() {
    delete [] hashArray;
    hashArray = NULL;
}

//copy constructor
Hash::Hash(const Hash &other) {
    sizeArray = other.sizeArray;
    numKeys = other.numKeys;
    outFile = other.outFile;
    int size = sizeArray;
    hashArray = new HashLinkedList[size];
    for (int i = 0; i < size; i++) {
        HashNode * temp = other.hashArray[i].getRoot();
        while(temp != NULL) {
            HashNode * added = hashArray[i].insert(temp->word);
            int count = temp->where.size();
            for (int j = 0; j < count; j++) {
                int index = temp->where[j];
                added->where.push_back(index);
            }
            temp = temp->next;
        }
    }
}

//assignment operator
Hash &Hash::operator=(const Hash &other) {
    if (this != &other) {
        sizeArray = other.sizeArray;
        numKeys = other.numKeys;
        outFile = other.outFile;
        int size = sizeArray;
        hashArray = new HashLinkedList[size];
        for (int i = 0; i < size; i++) {
            HashNode * temp = other.hashArray[i].getRoot();
            while(temp != NULL) {
                HashNode *added = hashArray[i].insert(temp->word);
                int count = temp->where.size();
                for (int j = 0; j < count; j++) {
                    int index = temp->where[j];
                    added->where.push_back(index);
                }
            }
        }
    }
    return *this;
}

//Function: converts string to key
//Input: string
//Returns: integer
//Does: changes the string to a number using ASCII
int Hash::convertKey(string word) {
    int key = 0;
    int size = word.size();
    for (int i = 0; i < size; i++) {
        if (word[i] > 64 and word[i] < 91) {
            word[i] = word[i] + 32;
        }
        key = key + ((word[i]*26)+7);
    }
    return key;
}

//Function: makes the key a smaller number
//Input: integer
//Returns: integer
//Does: makes the key a smaller number using mod
int Hash::Hash1(int key) {
    int num = key*.7;
    int size = sizeArray;
    key = num%size;
    return key;
}

//Function: makes the key a smaller number
//Input: integer
//Returns: integer
//Does: makes the key a smaller number using mod
int Hash::Hash2 (int key) {
    int num = key*.179;
    key = (num%2) + 3;
    return key;
}

//Function: combines the two hash funcitons
//Input: integer
//Returns: integer
//Does: takes the two hash values, adds them together, then
// makes it smaller and smaller till it is inside array size
// (to avoid collision)
int Hash::doubleHash(int key) {
    int hash1 = Hash1(key);
    int hash2 = Hash2(key);
    key = hash1+hash2;
    while (key > sizeArray-1 or key < 0) {
        key = key%3;
    }
    return key;
}

//Function: inserts a HashNode into the Hash
//Input: integer (key), string (word), integer (index of line in allLines)
//Returns: nothing
//Does: checks if node with that name already exists, creates a new
// node with LL insert if not, and adds line to where vector
void Hash::insert(int key, string name, int index) {
    HashNode * in = hashArray[key].search(name);
    if (in == NULL) {
        HashNode * temp = hashArray[key].insert(name);
        temp->where.push_back(index);
        numKeys++;
        double load = loadFactor();
        if (load > 0.8) {
            expandArray();
        }
    }
    else {
        in->where.push_back(index);
    }
}

//Function: checks ratio of nodes to buckets
//Input: none
//Returns: double (ratio)
//Does: calculates load factor with numKeys and sizeArray
double Hash::loadFactor() {
    double load = numKeys/sizeArray;
    return load;
}    

//Function: gets size of array
//Input: none
//Returns: integer
//Does: returns sizeArray
int Hash::getSize(){
    int size = sizeArray;
    return size;
}

//Function: gets number of keys in hash
//Input: none
//Returns: integer
//Does: returns numKeys
int Hash::getNumKeys() {
    return numKeys;
}

//Function: expands array
//Input: none
//Returns: nothing
//Does: creates a new heap allocated array with double the size
// then rehashes everything in the old array and populates the new
// array and deletes the old array
void Hash::expandArray() {
    int size = 2.1 * sizeArray;
    HashLinkedList * aux = new HashLinkedList[size];
    for(int i = 0; i < size; i++) {
        aux[i] = NULL;
    }
    int size2 = sizeArray;
    sizeArray = sizeArray*2.1;
    for (int j = 0; j < size2; j++) {
        HashNode * other = hashArray[j].getRoot();
        while (other != NULL) {
            string name = other->word;
            int key = convertKey(name);
            int index = doubleHash(key);
            HashNode * temp = aux[index].insert(name);
            int count = other->where.size();
            for (int i = 0; i < count; i++) {
                temp->where.push_back(other->where[i]);
            }
            other = other->next;
        }
    }
    delete [] hashArray;
    hashArray = aux;
}

//Function: find words and adds them to hashArray
//Input: string (line from file), integer (index of allLines that line is from)
//Returns: nothing
//Does: takes in a line and seperate words and adds them to the array
void Hash::takeWords(string line, int index) {
    int length = line.size();
    string word = "";
    for (int i = 0; i < length+1; i++) {
        if (line[i] == ' ' or i == length) {
            int key = convertKey(word);
            int num = doubleHash(key);
            insert(num, word, index);
            word.clear();
        }
        else {
            word.push_back(line[i]);
        }
    }
}

//Function: opens file and gets lines
//Input: string (file name)
//Returns: nothing
//Does: opens a file and uses get line to read the file
// calls takeWords to input words into HashArray
void Hash::hashFile(string file) {
    ifstream infile;
    infile.open(file);
    int count = 0;
    if (!infile.is_open()) {
        cerr << "Could not build index, exiting";
    }
    else {
        string line;
        while (getline(infile, line)) {
            count++;
            string number = std::to_string(count);
            string where = file + ":" + number + ": " + line;
            allLines.push_back(where);
            int size = allLines.size();
            takeWords(line, size-1);
        }
    }
    infile.close();
}

//Function: prints Where vector of HashNode with name input
//Input: HashNode pointer
//Returns: nothing
//Does: opens the outFile and allLine vector element of
// the indexes in the node's where vector
void Hash::printWhere(HashNode * node) {
    ofstream outfile;
    outfile.open(outFile, fstream::app);
    int size = node->where.size();
    string prev = "empty";
    for (int i = 0; i < size; i++) {
        string line = allLines[node->where[i]];
        if (prev != line) {
            outfile << line << endl;
        }
        prev = line;
    }
    outfile.close();
}

//Funciton: sets Output file
//Input: string (new file)
//Returns: nothing
//Does: sets private outFile to input and makes the file empty
void Hash::setOutfile(string file){
    ofstream outfile;
    outfile.open(file, std::ofstream::out |std::ofstream::trunc);
    outfile.close();
    outFile = file;
}

//Function: takes the word searches for it in hash and print where it is found
//Input: string
//Returns: nothing
//Does: loops through the word and sperates them adn querys them,
// prints where the word is found in outfile
void Hash::queryHelp(string word) {
    int length = word.size();
    string newWord;
    for (int i = 0; i < length+1; i++) {
        if (word[i] == ' ' or i == length) {
            bool done1 = false;
            bool done2 = false;
            newWord = removeFrontChar(newWord, done1);
            newWord = removeBackChar(newWord, done2);
            int num = convertKey(newWord);
            int index = doubleHash(num);
            HashNode * in = hashArray[index].search(newWord);
            if (in == NULL) {
                ofstream outfile;
                outfile.open(outFile, fstream::app);
                outfile << "query not found" << endl;
                outfile.close();
            }
            else {
                printWhere(in);
            }
            newWord.clear();
        }
        else {
            newWord.push_back(word[i]);
        }
    }
}

//Function: does everything relating to query
//Input: none
//Returns: nothing
//Does: keeps taking input and either quering,
// changing output file until done
void Hash::query() {
    string word;
    while (!cin.eof()) {
        cout << "Query? ";
        getline(cin, word);
        if (cin.eof()) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            break;
        }
        if (word[0] == '@') {
            if (word == "@quit" or word == "@q") {
                cout << "Goodbye! Thank you and have a nice day." << endl;
                break;
            }
            fInput(word);
            insen(word);
        }
        else {
            queryHelp(word);
        }
    }
}

//Function: change outputfile
//Input: string
//Returns: nothing
//Does: removes the "@f" and sets outFile to input
void Hash::fInput(string command) {
    if (command[1] == 'f' and command[2] == ' ') {
        command.erase(0,3);
        setOutfile(command);
    }
}

//Function: creates a tree
//Input: string
//Returns: nothing
//Does: creates a FSTree with the input and traverses tree
void Hash::buildTree(string file) {
    FSTree tree(file);
    DirNode * root = tree.getRoot();
    traverseTree(root, file);
}

//Function: traverses tree, opens files, reads files, and inserts words into Hash
//Input: DirNode pointer, string
//Returns: nothing
//Does: traverses through tree and when it reaches a file, it opens the
// file and calls hashFile to insert words from file to hash
void Hash::traverseTree(DirNode * temp, string mod) {
    int subDirs = temp->numSubDirs();
    int files = temp->numFiles();
    for (int i = 0; i < subDirs; i++) {
        DirNode * t =  temp->getSubDir(i);
        string newMod = mod + "/" + t->getName();
        traverseTree(t, newMod);
    }
    for (int j = 0; j < files; j++) {
        string name = mod + "/" + temp->getFile(j);
        hashFile(name);
    }
}

//Function:remove front nonalphanumeric characters from string
//Input: string and bool
//Returns: string
//Does: loops through string and removes the first character if
// it isn't alphanumeric
string Hash::removeFrontChar(string word, bool done) {
    while (done == false) {
        if ((word[0] < 48) or ((word[0] > 57) and (word[0] < 65)) or
            ((word[0] > 90) and (word[0] < 97)) or (word[0] > 123)) {
            word.erase(0,1);
        }
        else {
            done = true;
        }
    }
    return word;
}

//Function:remove back nonalphanumeric characters from string
//Input: string and bool
//Returns: string
//Does: loops through string and removes the last character if
// it isn't alphanumeric
string Hash::removeBackChar(string word, bool done) {
    while (done == false) {
        int s = word.size();
        if ((word[s-1] < 48) or ((word[s-1] > 57) and (word[s-1] < 65)) or
            ((word[s-1] > 90) and (word[s-1] < 97)) or (word[s-1] > 123)) {
            word.erase(s-2,s-1);
        }
        else {
            done = true;
        }
    }
    return word;
}

//Function: queries case insenitive words
//Input: string
//Returns: nothing
//Does: removes function "@i..." and takes the rest of the line
// and queries the words by making them lower case and calling printInsen
void Hash::insen(string line) {
    if (line[0] == '@' and line[1] == 'i') {
        int count = 0;
        string command = "";
        while (line[count] != ' ') {
            command.push_back(line[count]);
            line.erase(0,1);
        }
        line.erase(0,1);
        if (command == "@i" or command == "@insensitive") {
            int length = line.size();
            string newWord;
            for (int i = 0; i < length+1; i++) {
                if (line[i] == ' ' or i == length) {
                    bool front = false;
                    bool end = false;
                    newWord = removeFrontChar(newWord, front);
                    newWord = removeBackChar(newWord, end);
                    newWord = makeLowerCase(newWord);
                    int num = convertKey(newWord);
                    int index = doubleHash(num);
                    HashNode * root = hashArray[index].getRoot();
                    printInsen(root, newWord);
                    newWord.clear();
                }
                else {
                    newWord.push_back(line[i]);
                }
            }
        }
    }
}

//Function: makes a word all lowercase
//Input: string
//Returns: string
//Does: makes uppercase letter lowercase using ascii
string Hash::makeLowerCase(string word) {
    int size = word.size();
    string lowerCase = "";
    for (int i = 0; i < size; i++) {
        if (word[i] > 64 and word[i] < 91) {
            word[i] = word[i] + 32;
            lowerCase.push_back(word[i]);
        }
        else {
            lowerCase.push_back(word[i]);
        }
    }
    return lowerCase;
}

//Function: prints all places that a word appears in case insensitive command
//Input: HashNode pointer, string
//Returns: nothing
//Does: traverses through linked list and for each node in the list,
// it uses makeLowerCase for node word and checks it agaisnt input word
// if the same, it prints node where vector
void Hash::printInsen(HashNode * root, string name) {
    HashNode * temp = root;
    string word = "";
    while (temp != NULL) {
        word = makeLowerCase(temp->word);
        if (word == name) {
            printWhere(temp);
        }
        temp = temp->next;
    }
}
