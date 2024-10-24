/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which handles the automation of the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 1.0
 */
 
#ifndef PROJECT_VACCINE_H
#define PROJECT_VACCINE_H

#include <string>
#include <iostream>
#include "../XmlParser/tinyxml.h"

using namespace std;

class Vaccine {
    Vaccine* _initCheck;

    string type; // Type van vaccin
    int levering; // Aantal geleverde vaccins per interval
    int interval;
    int transport; // Aantal vaccins per transport
    int hernieuwing; // Tijd tussen hernieuwing
    int temperatuur;

public:
    /**
     \n Constructor
     \n ENSURE(this->properlyInitialised(), "Constructor must end properly initialised")
     */
    Vaccine();
    /**
     \n contructor
     \n ENSURE(this->properlyInitialised(), "Constructor must end properly initialised")
     * @param t:    type
     * @param l:    delivery
     * @param i:    interval
     * @param tr:   transport
     * @param h:    renewal
     * @param temp: temperature
     */
    Vaccine(string t, int l, int i, int tr, int h, int temp);

    /**
     \n Initialisation check
     * @return  Bool whether class object is initialised
     */
    bool properlyInitialised() const;

    /**
     \n Checks whether vaccine is empty
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when checking empty")
     * @return  Bool whether
     */
    bool empty();

    /**
     \n Add data from parsed XML element to vaccine
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when inserting data")
     * @param el:   The element
     */
    bool insert(TiXmlElement* el, ostream& errStr);


    //
    // Setters
    //

    /**
     \n Set the type of the vaccine
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting type")
     \n REQUIRE(t.size() > unsigned (0), "Vaccine type is empty")
     \n ENSURE(getType() == t, "setType postcondition failed")
     * @param t:    Given type
     */
    void setType(string& t);
    /**
     \n Set amount of vaccines per resupply
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting levering")
     \n REQUIRE(l > 0, "Vaccine leveringen must be bigger than 0")
     \n ENSURE(getLevering() == l, "setLevering postcondition failed")
     * @param l:    Amount to resupply
     */
    void setLevering(int l);
    /**
     \n Set interval between resupplies
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting interval")
     \n REQUIRE(i >= 0, "Vaccine can't have negative interval")
     \n ENSURE(getInterval() == i, "setInterval postcondition failed")
     * @param i:    interval amount
     */
    void setInterval(int i);
    /**
     \n Set amount of vaccines per transport
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting type")
     \n REQUIRE(t > 0, "Vaccine transport must be bigger than 0")
     \n ENSURE(getTransport() == t, "setTransport postcondition failed")
     * @param t:    Amount per transport
     */
    void setTransport(int t);
    /**
     \n Set time before second injection
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting hernieuwing")
     \n REQUIRE(h >= 0, "Vaccine can't have negative renewal")
     \n ENSURE(getHernieuwing() == h, "setHernieuwing postcondition failed")
     * @param h:    Interval between injections
     */
    void setHernieuwing(int h);
    /**
     \n Set storage temperature
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting temperature")
     \n ENSURE(getTemperatuur() == t, "setTemperature postcondition failed")
     * @param t:    Temperature to store vaccine
     */
    void setTemperatuur(int t);

    //
    // Getters
    //

    /**
     \n Get type of vaccine
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting type");
     * @return  The vaccine type
     */
    string getType() const;
    /**
     \n Get resupply amount
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting levering");
     * @return  Resupply amount
     */
    int getLevering() const;
    /**
     \n Get interval between resupplies
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting interval");
     * @return  Interval time
     */
    int getInterval() const;
    /**
     \n Get transport amount
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting transport");
     * @return  Amount per transport
     */
    int getTransport() const;
    /**
     \n Get time before renewal of injection
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting renewal");
     * @return  Time before renewal
     */
    int getHernieuwing() const;
    /**
     \n Get storage temperature
     \n REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting temperature");
     * @return  Temperature
     */
    int getTemperatuur() const;
};


#endif //PROJECT_VACCINE_H
