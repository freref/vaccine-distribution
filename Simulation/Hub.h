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

using namespace std;

class Centrum;

/**
 * Class which represents a vaccination hub in the simulation
 */
class Hub {
    Hub* _initCheck;

    int levering;
    int voorraad;
    int interval;
    int transport;
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
    Hub(int l, int i, int t, map<string, Centrum*> c);

    /**
     * \n checks of Hub is propperly initialized
     * @return
     */
    bool properlyInitialised() const { return _initCheck == this; }

    //setters
    /**
     * \n setter for delivery
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setLevering");
       \n REQUIRE(l>=0, "levering amount can't be negative");
       \n ENSURE(getLevering() == l, "setLevering postconditions failed");
     * @param l
     */
    void setLevering(int l);
    /**
     * \n setter for storage
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setVoorraad");
       \n REQUIRE(v>=0, "stock amount can't be negative");
       \n ENSURE(getVoorraad() == v, "setVoorraad postconditions failed");
     * @param v
     */
    void setVoorraad(int v);
    /**
     * \n setter for interval
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setInterval");
       \n REQUIRE(i>=0, "interval can't be negative");
       \n ENSURE(getInterval() == i, "setInterval postconditions failed");
     * @param i
     */
    void setInterval(int i);
    /**
     * \n setter for transport
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setTransport");
       \n REQUIRE(t>=0, "transport amount can't be negative");
       \n ENSURE(getTransport() == t, "setTransport postconditions failed");
     * @param t
     */
    void setTransport(int t);
    /**
     * \n setter for centrum
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
       \n REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
     * @param c
     */
    void setCentra(const map<string, Centrum*>& c);

    //getters
    /**
     * \n getter for delivery
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getLevering");
       \n ENSURE(amount>=0, "getLevering postconditions failed");
     * @return
     */
    int getLevering() const;
    /**
     * \n getter for supply
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVoorraad");
       \n ENSURE(amount>=0, "getVoorraad postconditions failed");
     * @return
     */
    int getVoorraad() const;
    /**
     * \n getter for interval
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getInterval");
       \n ENSURE(amount>=0, "getInterval postconditions failed");
     * @return
     */
    int getInterval() const;
    /**
     * \n getter for transport
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getTransport");
       \n ENSURE(amount>=0, "getTransport postconditions failed");
     * @return
     */
    int getTransport() const;
    /**
     * \n getter for centra
     * \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
       \n ENSURE(size>=1, "getCentra postconditions failed");
     * @return
     */
    const map<string, Centrum*>& getCentra() const;
};


#endif //PROJECT_HUB_H
