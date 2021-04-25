//
// Created by sande on 25/04/2021.
//

#include <string>
#include <sstream>

#include "algemeen.h"

using namespace std;

// https://stackoverflow.com/questions/4442658/c-parse-int-from-string
int stoi(string s) {
    if (s.empty())
        throw std::invalid_argument("conversion from invalid string to int");
    for (long unsigned int j=0; j<s.size(); j++) {
        if ((s[j] < '0' || s[j] > '9') && s[j] != '-')
            throw std::invalid_argument("conversion from invalid string to int");
    }
    int i;
    istringstream(s) >> i;
    return i;
}

