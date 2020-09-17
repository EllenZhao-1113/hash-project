//Ellen Zhao
//Project 2
//COMP15
//Spring 2019
//remove non-alphanumerics
//

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//remove front nonalphanumeric characters from string
string removeFrontChar(string word, bool done);
//remove back nonalphanumeric characters fron string
string removeBackChar(string word, bool done);

//gets rid of non-alphanumeric characters by ysing ascii table
int main() {
    string word;
    while (!cin.eof()) {
      bool front = false;
      bool end = false;
        if (cin.eof()) {
            break;
        }
        cin >> word;
        if (word == "@quit" or word == "@q") {
            break;
        }
        word = removeFrontChar(word, front);
        word = removeBackChar(word, end);
        cout << word << endl;
    }
    return 0;
}

//Function:remove front nonalphanumeric characters from string
//Input: string and bool
//Returns: string
//Does: loops through string and removes the first character if
// it isn't alphanumeric
string removeFrontChar(string word, bool done) {
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
string removeBackChar(string word, bool done) {
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
