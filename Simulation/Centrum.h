/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class which represents a vaccination center
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

#include <string>
#include <vector>

using namespace std;

/**
 * Class which represents a vaccination centre in the simulation
 */
class Centrum {
    Centrum* _initCheck = NULL;

    string naam;
    string adres;
    int inwoners;
    int capaciteit;
    int vaccins;
    int gevaccineerd;
public:
    //constructor
    Centrum();
    /**
     * Constructor
     * @param n:    Name
     * @param a:    Adres
     * @param i:    Inhabitants amount
     * @param c:    Capacity
     */
    Centrum(const string& n, const string& a, int i, int c);

    bool properlyInitialised() const {return _initCheck == this; };

    void setVaccins(int v);
    void setGevaccineerd(int g);

    const string &getNaam() const;
    const string &getAdres() const;
    int getInwoners() const;
    int getCapaciteit() const;
    int getVaccins() const;
    int getGevaccineerd() const;
};


#endif //PROJECT_CENTRUM_H
