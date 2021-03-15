/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the Hub class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Hub.h"
#include "../DesignByContract.h"

Hub::Hub() {
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

Hub::Hub(int l, int i, int t, map<string, Centrum *> c) {
    REQUIRE(l>=0, "levering amount can't be negative");
    REQUIRE(i>=0, "interval can't be negative");
    REQUIRE(t>=0, "transport amount can't be negative");
    REQUIRE(c.size()>=1, "must atleast contain 1 centrum");
    levering = l;
    voorraad = l;
    interval = i;
    transport = t;
    centra = c;
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

// Setters

void Hub::setLevering(int l) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setLevering");
    REQUIRE(l>=0, "levering amount can't be negative");
    levering = l;
    ENSURE(getLevering() == l, "setLevering postconditions failed");
}

void Hub::setVoorraad(int v) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setVoorraad");
    REQUIRE(v>=0, "stock amount can't be negative");
    voorraad = v;
    ENSURE(getVoorraad() == v, "setVoorraad postconditions failed");
}

void Hub::setInterval(int i) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setInterval");
    REQUIRE(i>=0, "interval can't be negative");
    interval = i;
    ENSURE(getInterval() == i, "setInterval postconditions failed");
}

void Hub::setTransport(int t) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setTransport");
    REQUIRE(t>=0, "transport amount can't be negative");
    transport = t;
    ENSURE(getTransport() == t, "setTransport postconditions failed");
}

void Hub::setCentra(const map<string, Centrum *> &c) {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling setCentra");
    REQUIRE(c.size() >= 1, "hub must at least contain 1 centrum");
    centra = c;
}

// Getters

int Hub::getLevering() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getLevering");
    int amount = levering;
    ENSURE(amount>=0, "getLevering postconditions failed");
    return amount;
}

int Hub::getVoorraad() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getVoorraad");
    int amount = voorraad;
    ENSURE(amount>=0, "getVoorraad postconditions failed");
    return amount;
}

int Hub::getInterval() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getInterval");
    int amount = interval;
    ENSURE(amount>=0, "getInterval postconditions failed");
    return amount;
}

int Hub::getTransport() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getTransport");
    int amount = transport;
    ENSURE(amount>=0, "getTransport postconditions failed");
    return amount;
}

const map<string, Centrum *>& Hub::getCentra() const {
    REQUIRE(this->properlyInitialised(), "hub wasn't initialised when calling getCentra");
    int size = centra.size();
    ENSURE(size>=1, "getCentra postconditions failed");
    return centra;
}
