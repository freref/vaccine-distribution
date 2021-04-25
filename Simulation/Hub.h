/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which represents a vaccination hub
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

#include <string>
#include <vector>
#include <map>
#include "Vaccine.h"

using namespace std;

class Centrum;

/**
 * Class which represents a vaccination hub in the simulation
 */
class Hub {
    Hub* _initCheck;

    int totaleVoorraad;
    vector<Vaccine*> vaccins;
    map<string, Centrum*> centra;
public:
    //constructor
    Hub();
    /**
     * \n constructor
     * \n REQUIRE(l>=0, "levering amount can't be negative");
       \n REQUIRE(i>=0, "interval can't be negative");
       \n REQUIRE(t>=0, "transport amount can't be negative");
       \n REQUIRE(!c.empty(), "must atleast contain 1 centrum");
     * @param l
     * @param i
     * @param t
     * @param c
     */
    Hub(vector<Vaccine*> vaccins, map<string, Centrum*> c);
    /**
     * \n checks of Hub is propperly initialized
     * @return
     */
    bool properlyInitialised() const { return _initCheck == this; }

    //setters

    /**



     * \n setter for centrum
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
       \n REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
     * @param c
     */
    void setCentra(const map<string, Centrum*>& c);
    /**
     * \n getter for supply
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVoorraad");
       \n ENSURE(amount>=0, "getVoorraad postconditions failed");
     * @return
     */
    int accessorTotaleVoorraad();
    /**
     * \n getter for centra
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
       \n ENSURE(size>=1, "getCentra postconditions failed");
     * @return
     */
    const map<string, Centrum*>& getCentra() const;

    vector<Vaccine*> getVaccins();
};


#endif //PROJECT_HUB_H
