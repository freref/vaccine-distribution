/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the Hub class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Hub.h"
#include "Centrum.h"
#include "DesignByContract.h"

Hub::Hub() {
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

Hub::Hub(vector<Vaccine*> v, map<string, Centrum *> c) {
    REQUIRE(!c.empty(), "hub must at least contain 1 centrum");
    REQUIRE(!v.empty(), "hub must at least contain 1 vaccine");
    _initCheck = this;
    vaccins = v;
    centra = c;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

Hub::~Hub() {
    for (unsigned int i = 0; i < vaccins.size(); i++) {
        delete vaccins[i];
    }
}

void Hub::verhoogVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] += aantal;
}

void Hub::verlaagVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] -= aantal;
}

void Hub::setVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = aantal;
}

int Hub::getVoorraad(Vaccine* vac){
    return voorraad[vac];
}

int Hub::getTotaleVoorraad() const {
    int v = 0;
    map<Vaccine*, int>::const_iterator it = voorraad.begin();

    for(it = voorraad.begin(); it != voorraad.end(); it++){
        v += it->second;
    }

    return v;
}

//
// Setters
//
void Hub::setCentra(const map<string, Centrum *> &c) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
    REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
    centra = c;
}

void Hub::setVaccins(const vector<Vaccine *> &vaccines) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setVaccins");
    REQUIRE(!vaccines.empty(), "hub must at least contain 1 vaccine");
    this->vaccins = vaccines;
}

void Hub::addCentrum(Centrum* centrum) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling addCentrum");
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't intialised when adding to hub");
    unsigned int oSize = centra.size();
    string cNaam = centrum->getNaam();
    centra.insert(make_pair(cNaam, centrum));
    ENSURE(getCentra().size() == oSize + 1, "addCentrum postcondition failed");
}

void Hub::addVaccine(Vaccine *vaccine) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when callind addVaccine");
    REQUIRE(vaccine->properlyInitialised(), "vaccine wasn't initialised when adding to hub");
    unsigned int oSize = vaccins.size();
    vaccins.push_back(vaccine);
    ENSURE(getVaccins().size() == oSize + 1, "addVaccine postcondition failed");
}

//
// Getters
//
const map<string, Centrum *>& Hub::getCentra() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
    int size = centra.size();
    ENSURE(size>=1, "getCentra postconditions failed");
    return centra;
}

vector<Vaccine*> Hub::getVaccins() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVaccins");
    return vaccins;
}