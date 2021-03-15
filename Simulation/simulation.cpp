/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the simulation class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#include "simulation.h"
#include "Centrum.h"
#include "Hub.h"
#include "../DesignByContract.h"

simulation::simulation() {
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

simulation::~simulation() {
    vector<Hub*>::iterator hIt;
    delete hub;
    vector<Centrum*>::iterator cIt;
    for (cIt = centra.begin(); cIt != centra.end(); cIt++) {
        delete *cIt;
    }
    _initCheck = NULL;
}

bool simulation::properlyInitialised() const {
    return _initCheck == this;
}

void simulation::addCentrum(Centrum* c) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling addCentrum");
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialised when calling addCentrum");
    centra.push_back(c);
    ENSURE(centra[centra.size()-1] == c, "addCentrum postconditions failed");
}

Hub* simulation::getHub() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling hetHub");
    REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling getHub");
    return hub;
}

const vector<Centrum*> &simulation::getCentra() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra");
    return centra;
}
