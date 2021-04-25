/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the Hub class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Hub.h"
#include "DesignByContract.h"

Hub::Hub() {
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

Hub::Hub(vector<Vaccine*> v, map<string, Centrum *> c) {
    REQUIRE(!c.empty(), "must atleast contain 1 centrum");
    vaccins = v;
    centra = c;
    accessorTotaleVoorraad();
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

int Hub::accessorTotaleVoorraad(){
    int v = 0;
    for(unsigned int i = 0; i < vaccins.size(); i++){
        v += vaccins[i]->getVoorraad();
    }
    totaleVoorraad = v;
    return totaleVoorraad;
}

// Setters

void Hub::setCentra(const map<string, Centrum *> &c) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
    REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
    centra = c;
}


const map<string, Centrum *>& Hub::getCentra() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
    int size = centra.size();
    ENSURE(size>=1, "getCentra postconditions failed");
    return centra;
}

vector<Vaccine*> Hub::getVaccins(){
    return vaccins;
}