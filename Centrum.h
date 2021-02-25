//
// Created by Frederic Hamelink on 25/02/2021.
//

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

#include <string>
#include <vector>

using namespace std;

class Centrum {
    string naam;
    string adres;
    int inwoners;
    int capaciteit;
public:
    //constructor
    Centrum(string n, string a, int i, int c){
        naam = n;
        adres = a;
        inwoners = i;
        capaciteit = c;
    };
};


#endif //PROJECT_CENTRUM_H
