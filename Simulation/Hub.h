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
    /**
     \n Empty constructor
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised")
     */
    Hub();
    /**
     \n constructor
     \n REQUIRE(!c.empty(), "hub must at least contain 1 centrum")
     \n REQUIRE(!v.empty(), "hub must at least contain 1 vaccine")
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised")
     \n ENSURE(getVaccins() == vaccins && getCentra() == c, "Hub constructor postconditions failed")
     @param vaccins:  Vaccines in the hub
     @param c:        Centra in hub
     */
    Hub(vector<Vaccine*> vaccins, map<string, Centrum*> c);
    /**
     \n Destructor
     */
    ~Hub();

    /**
     \n checks whether Hub is propperly initialized
     @return    Properly initialised
     */
    bool properlyInitialised() const { return _initCheck == this; }

    //setters

    /**
     \n Decrease stock of given vaccine
     \n REQUIRE(this->properlyInitialised(), "hub was't initialised when decreasing stock")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when decreasing stock")
     \n REQUIRE(getVoorraad(vac) - aantal >= 0, "vaccine stock can't go negative")
     \n ENSURE(oAmount - aantal == getVoorraad(vac), "verlaagVoorraad postcondition failed")
     * @param vac:      Vaccine for which to decrease stock
     * @param aantal:   Amount to decrease
     */
    void verlaagVoorraad(Vaccine* vac, int aantal);

    /**
     \n Increase stock of given vaccine
     \n REQUIRE(this->properlyInitialised(), "hub was't initialised when increasing stock")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when increasing stock")
     \n ENSURE(oAmount + aantal == getVoorraad(vac), "verhoogVoorraad postcondition failed")
     * @param vac:      Vaccine for which to increase stock
     * @param aantal:   Amount to increase
     */
    void verhoogVoorraad(Vaccine* vac, int aantal);

    /**
     \n Set stock of given vaccine
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when setting stock")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when setting stock")
     \n REQUIRE(aantal >= 0, "vaccine stock can't be negative")
     * @param vac:      Vaccine for which to set stock
     * @param aantal:   Amount to set
     */
    void setVoorraad(Vaccine* vac, int aantal);

    /**
     \n Get stock of given vaccine
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when getting stock of vacine")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when getting stock")
     * @param vac:  Vaccine to get stock of
     * @return  Current stock
     */
    int getVoorraad(Vaccine* vac);

    /**
     \n Get total stock amount
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when getting stock")
     * @return  Total stock
     */
    int getTotaleVoorraad() const;

    /**
     \n setter for centrum
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra")
     \n REQUIRE(!c.empty(), "hub must at least contain 1 centrum")
     \n ENSURE(getCentra() == c, "setCentra postcondition failed")
     * @param c:    Map containing centra linked to name
     */
    void setCentra(const map<string, Centrum*>& c);
    /**
     \n Set all vaccins in hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setVaccins")
     \n REQUIRE(!vaccines.empty(), "hub must at least contain 1 vaccine")
     \n ENSURE(getVaccins() == vaccines, "setVaccins postcondition failed")
     * @param vaccines: Vector containing vaccins
     */
    void setVaccins(const vector<Vaccine*>& vaccines);

    /**
     \n Add single centrum to the hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling addCentrum")
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't intialised when adding to hub")
     \n ENSURE(getCentra().size() == oSize + 1, "addCentrum postcondition failed")
     * @param centrum:  Centrum to add
     */
    void addCentrum(Centrum* centrum);
    /**
     \n Add single vaccine to the hub
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when callind addVaccine")
     \n REQUIRE(vaccine->properlyInitialised(), "vaccine wasn't initialised when adding to hub")
     \n ENSURE(getVaccins().size() == oSize + 1, "addVaccine postcondition failed")
     * @param vaccine:  Vaccine to add
     */
    void addVaccine(Vaccine* vaccine);

    /**
     \n getter for centra
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
     \n ENSURE(size>=1, "getCentra postconditions failed");
     * @return  Centra in hub
     */
    const map<string, Centrum*>& getCentra() const;
    /**
     \n Get the vaccins
     \n REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVaccins")
     * @return  Vaccines in hub
     */
    vector<Vaccine*> getVaccins() const;
};


#endif //PROJECT_HUB_H
