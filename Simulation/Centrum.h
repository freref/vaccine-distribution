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
    int vaccins;
    int gevaccineerd;
public:
    //constructor
    Centrum(const string& n, const string& a, int i, int c){
        naam = n;
        adres = a;
        inwoners = i;
        capaciteit = c;
        vaccins = 0;
        gevaccineerd = 0;
    };

    const string &getNaam() const {
        return naam;
    }

    const string &getAdres() const {
        return adres;
    }

    int getInwoners() const {
        return inwoners;
    }

    int getCapaciteit() const {
        return capaciteit;
    }

    int getVaccins() const {
        return vaccins;
    }

    int getGevaccineerd() const {
        return gevaccineerd;
    }
};


#endif //PROJECT_CENTRUM_H
