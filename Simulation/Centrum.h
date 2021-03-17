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
    Centrum* _initCheck;

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
     * \n REQUIRE(i>=0, "inhabitant amount can't be negative");
       \n REQUIRE(c>=0, "capacity can't be negative");
     * \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
     * @param n:    Name
     * @param a:    Adres
     * @param i:    Inhabitants amount
     * @param c:    Capacity
     */
    Centrum(const string& n, const string& a, int i, int c);

    /**
     * Checks if propperly initialized
     * @return bool
     */
    bool properlyInitialised() const {return _initCheck == this; };

    /**
     * \n setter for vaccines
       \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
       \n REQUIRE(v>=0, "vaccins can't be set to negative");
       \n REQUIRE(v<=getCapaciteit()*2, "vaccins can't exceed capacity*2");
       \n ENSURE(getVaccins() == v, "setVaccins postcondition failed");
     * @param v int vaccines
     */
    void setVaccins(int v);

    /**
     * \n setter for injected
       \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setGevaccineerd");
       \n REQUIRE(g>=0, "gevaccineerd can't be negative");
       \n REQUIRE(g<=getInwoners(), "gevaccineerd amount can't be bigger than inhabitants amount");
       \n ENSURE(getGevaccineerd() == g, "setGevaccineerd postcondition failed");
     * @param g int injections
     */
    void setGevaccineerd(int g);

    /**
     * \n getter for name
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getNaam");
     * @return string name
     */
    const string &getNaam() const;
    /**
     * \n getter for address
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getAdres");
     * @return string address
     */
    const string &getAdres() const;
    /**
     * \n getter for inhabitants
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
     * \n ENSURE(amount>=0, "getInwoners postconditions failed");
     * @return int inhabitants
     */
    int getInwoners() const;
    /**
     * getter for capacity
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getCapaciteit");
     * \n ENSURE(amount>=0, "getCapaciteit postconditions failed");
     * @return int
     */
    int getCapaciteit() const;
    /**
     * getter for vaccines
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVaccins");
     * \n ENSURE((amount>=0) && (amount<=getCapaciteit()*2), "getVaccins postconditions failed");
     * @return int
     */
    int getVaccins() const;
    /**
     * \n getter for vaccinated
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd");
       \n ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed");
     * @return int
     */
    int getGevaccineerd() const;
};


#endif //PROJECT_CENTRUM_H
