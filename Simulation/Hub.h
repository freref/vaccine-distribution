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

    map<Vaccine*, int> voorraad;
    vector<Vaccine*> vaccins;
    map<string, Centrum*> centra;
public:
    //constructor
    Hub();
    /**
     \n constructor
     \n REQUIRE(!c.empty(), "hub must at least contain 1 centrum")
     \n REQUIRE(!v.empty(), "hub must at least contain 1 vaccine")
     * @param vaccins:  Vaccines in the hub
     * @param c:        Centra in hub
     */
    Hub(vector<Vaccine*> vaccins, map<string, Centrum*> c);
    /**
     * Destructor
     */
    ~Hub();

    /**
     * \n checks of Hub is propperly initialized
     * @return
     */
    bool properlyInitialised() const { return _initCheck == this; }

    //setters

    void verlaagVoorraad(Vaccine* vac, int aantal);

    void verhoogVoorraad(Vaccine* vac, int aantal);

    void setVoorraad(Vaccine* vac, int aantal);

    int getVoorraad(Vaccine* vac);

    int getTotaleVoorraad();

    /**
     \n setter for centrum
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
     \n REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
     * @param c
     */
    void setCentra(const map<string, Centrum*>& c);
    /**
     \n Set all vaccins in hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setVaccins")
     \n REQUIRE(!vaccines.empty(), "hub must at least contain 1 vaccine");
     * @param vaccines: Vector containing vaccins
     */
    void setVaccins(const vector<Vaccine*>& vaccines);

    /**
     \n Add single centrum to the hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling addCentrum")
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't intialised when adding to hub")
     \n ENSURE(getCentra().size() == oSize + 1, "addCentrum postcondition failed")
     * @param centrum
     */
    void addCentrum(Centrum* centrum);
    /**
     \n Add single vaccine to the hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when callind addVaccine")
     \n REQUIRE(vaccine->properlyInitialised(), "vaccine wasn't initialised when adding to hub")
     \n ENSURE(getVaccins().size() == oSize + 1, "addVaccine postcondition failed")
     * @param vaccine
     */
    void addVaccine(Vaccine* vaccine);

    /**
     \n getter for centra
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
     \n ENSURE(size>=1, "getCentra postconditions failed");
     * @return
     */
    const map<string, Centrum*>& getCentra() const;
    /**
     \n Get the vaccins
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVaccins")
     * @return
     */
    vector<Vaccine*> getVaccins() const;
};


#endif //PROJECT_HUB_H
