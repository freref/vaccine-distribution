/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the Centrum class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Centrum.h"
#include "DesignByContract.h"

Centrum::Centrum() {
    naam = "";
    adres = "";
    inwoners = 0;
    capaciteit = 0;
    vaccins = 0;
    gevaccineerd = 0;
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

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

void Centrum::setVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = aantal;
}

map<Vaccine*, int> Centrum::getVoorraad(){
    return voorraad;
}

void Centrum::verhoogVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = getVoorraad()[vac] + aantal;
}

void Centrum::verlaagVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = getVoorraad()[vac] - aantal;
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

int Centrum::getVaccins() {
    int amount = 0;
    map<Vaccine*, int> v = getVoorraad();
    for (map<Vaccine*, int>::iterator it = v.begin(); it != v.end(); it++) {
        amount += it->second;
    }
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
