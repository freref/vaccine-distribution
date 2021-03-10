//
// Created by sande on 4/03/2021.
//

#include "simulation.h"
#include "Centrum.h"
#include "Hub.h"

simulation::simulation() {
    _initCheck = this;
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
    centra.push_back(c);
}

Hub* simulation::getHub() const {
    return hub;
}

const vector<Centrum*> &simulation::getCentra() const {
    return centra;
}
