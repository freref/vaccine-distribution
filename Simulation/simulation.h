/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which stores and handles the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 2.0
 */

#ifndef PROJECTPSE_SIMULATION_H
#define PROJECTPSE_SIMULATION_H

#include <vector>
#include <map>
#include "Vaccine.h"

using namespace std;

// Forward declaration of necessary classes
class Hub;
class Centrum;


class simulation {
    map<string, int> deliveries_by_type;
    vector<Hub*> hubs;
    vector<Centrum*> centra;
    simulation* _initCheck;
public:
    /**
     \n Constructor
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised")
     */
    simulation();
    /**
     \n Destructor
     */
    ~simulation();
    /**
     \n Initialisation check
     @return  Whether class is initialised
     */
    bool properlyInitialised() const;

    /**
     \n Clears the simulation class
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling clear")
     \n ENSURE(getCentra().empty(), "centra didn't clear correctly")
     \n ENSURE(getHubs().empty(), "hubs didn't clear correctly")
     \n ENSURE(getDeliveries().empty(), "deliveries didn't clear correctly")
     */
    void clear();

    /**
     \n Creates a simple graphical impression of the simulation
     \n REQUIRE(this->properlyInitialised(), "Simulation wasn't initialised when creating graphic impression")
     \n REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when creating simple impression")
     \n REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when creating simple impression")
     @param oStream:    Output stream
     */
    void graphicImpression(ostream& oStream);
    /**
     \n Export the simulation data
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling exporter")
     \n REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when exporting simulation")
     \n REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when exporting simulation")
     @param ostream:    Output stream
     */
    void exportSim(ostream& ostream);

    /**
     \n Export simulation stats gathered during auto simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when exporting stats")
     \n REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when exporting stats")
     \n REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when exporting stats")
     @param oStream:    Output stream
     */
    void stats(ostream& oStream);

    //
    // Getters, Setters
    //
    /**
     \n Sets the hubs in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub")
     \n REQUIRE(!h.empty(), "simulation must contain at least 1 hub")
     \n ENSURE(getHubs() == h, "setHubs postcondition failed")
     @param h:  Vector containing hubs to be added
     */
    void setHubs(vector<Hub*> h);
    /**
     \n Add a centrum to the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling addCentrum")
     \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialised when calling addCentrum")
     \n ENSURE(getCentra().size() == oSize+1, "addCentrum postconditions failed")
     @param c:   to be added centra
     */
    void addCentrum(Centrum* c);
    /**
     \n Set all centra in simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setCentra")
     \n REQUIRE(!c.empty(), "simulations must contain at least 1 centrum")
     \n ENSURE(getCentra().size() == c.size(), "setCentra postcondition failed")
     @param c:   The vector containing to ba added centra
     */
    void setCentra(const vector<Centrum*>& c);

    /**
     \n Get the simulations hub
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub")
     @return The hub
     */
    vector<Hub*> getHubs() const;
    /**
     \n Get the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra")
     @return The centra
     */
    const vector<Centrum*> &getCentra() const;

    /**
     \n Adds stats for delivery of certain vaccine type
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when adding delivery")
     \n REQUIRE(getDeliveries()[type] + aantal >= 0, "deliveries can't go into negative")
     \n ENSURE(oAmount + aantal == getDeliveries()[type], "addDelivery postcondition failed")
     @param type:     Type of delivered vaccine
     @param aantal:   Amount of delivered vaccine
     */
    void addDelivery(string type, int aantal);

    /**
     \n Get the made deliveries
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when getting deliveries")
     @return map containing deliveries per vaccine type
     */
    map<string, int>& getDeliveries();
};


#endif //PROJECTPSE_SIMULATION_H
