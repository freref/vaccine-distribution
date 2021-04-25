/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which stores and handles the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#ifndef PROJECTPSE_SIMULATION_H
#define PROJECTPSE_SIMULATION_H

#include <vector>
#include "Vaccine.h"

using namespace std;

// Forward declaration of necessary classes
class Hub;
class Centrum;


class simulation {
    Hub* hub;
    vector<Centrum*> centra;
    simulation* _initCheck;
public:
    /**
     \n Constructor
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
     */
    simulation();
    /**
     \n Destructor
     */
    ~simulation();
    /**
     \n Initialisation check
     * @return  Whether class is initialised
     */
    bool properlyInitialised() const;

    /**
     \n Clears the simulation class
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling clear")
     \n ENSURE(getHub() == NULL && getCentra().empty(), "clear postconditions failed")
     */
    void clear();

    void graphicImpression();

    /**
     \n Sets the hub in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub")
     \n REQUIRE(h->properlyInitialised(), "hub wasn't initialised when calling setHub")
     \n ENSURE(getHub() == h, "setHub postconditions failed")
     *  @param h The hub to be added
     */
    void setHub(Hub* const h);
    /**
     \n Add a centrum to the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling addCentrum")
     \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialised when calling addCentrum")
     \n ENSURE(getCentra().size() == oSize+1, "addCentrum postconditions failed")
     *  @param c    to be added centra
     */
    void addCentrum(Centrum* c);
    /**
     \n Set all centra in simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setCentra")
     \n REQUIRE(!c.empty(), "simulations must contain at least 1 centrum")
     \n ENSURE(getCentra().size() == c.size(), "setCentra postcondition failed")
     *  @param c    The vector containing to ba added centra
     */
    void setCentra(const vector<Centrum*>& c);

    /**
     \n Get the simulations hub
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub")
     *  @return The hub
     */
    Hub* getHub() const;
    /**
     \n Get the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra")
     *  @return The centra
     */
    const vector<Centrum*> &getCentra() const;

    void exportSim(ostream& ostream);
};


#endif //PROJECTPSE_SIMULATION_H
