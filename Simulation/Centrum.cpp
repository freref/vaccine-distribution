/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the Centrum class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Centrum.h"
#include "../DesignByContract.h"

Centrum::Centrum(const string &n, const string &a, int i, int c) {
    REQUIRE(i>=0, "inhabitant amount can't be negative");
    REQUIRE(c>=0, "capacity can't be negative");
    naam = n;
    adres = a;
    inwoners = i;
    capaciteit = c;
    vaccins = 0;
    gevaccineerd = 0;
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

void Centrum::setVaccins(int v) {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
    REQUIRE(v>=0, "vaccins can't be set to negative");
    REQUIRE(v<=getCapaciteit()*2, "vaccins can't exceed capacity*2");
    vaccins = v;
    ENSURE(getVaccins() == v, "setVaccins postcondition failed");
}

void Centrum::setGevaccineerd(int g) {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setGevaccineerd");
    REQUIRE(g>=0, "gevaccineerd can't be negative");
    REQUIRE(g<=getInwoners(), "gevaccineerd amount can't be bigger than inhabitants amount");
    gevaccineerd = g;
    ENSURE(getGevaccineerd() == g, "setGevaccineerd postcondition failed");
}

const string & Centrum::getNaam() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getNaam");
    return naam;
}

const string & Centrum::getAdres() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getAdres");
    return adres;
}

int Centrum::getGevaccineerd() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd");
    int amount = gevaccineerd;
    ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed");
    return amount;
}

int Centrum::getVaccins() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVaccins");
    int amount = vaccins;
    ENSURE((amount>=0) && (amount<=getCapaciteit()*2), "getVaccins postconditions failed");
    return amount;
}

int Centrum::getCapaciteit() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getCapaciteit");
    int amount = capaciteit;
    ENSURE(amount>=0, "getCapaciteit postconditions failed");
    return amount;
}

int Centrum::getInwoners() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
    int amount = inwoners;
    ENSURE(amount>=0, "getInwoners postconditions failed");
    return amount;
}
