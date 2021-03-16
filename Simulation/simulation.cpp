/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the simulation class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#include <iostream>
#include "simulation.h"
#include "Centrum.h"
#include "Hub.h"
#include "../DesignByContract.h"

simulation::simulation() {
    _initCheck = this;
    hub = NULL;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

simulation::~simulation() {
    if (hub)
        delete hub;
    if (!centra.empty()) {
        vector<Centrum *>::iterator cIt;
        for (cIt = centra.begin(); cIt != centra.end(); cIt++) {
            delete *cIt;
        }
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

void simulation::setCentra(const vector<Centrum *> &c) {
    REQUIRE(this->properlyInitialised(), "simulation zasn't initialised when calling setCentra");
    REQUIRE(!c.empty(), "simulations must contain at least 1 centrum");
    centra = c;
}

Hub* simulation::getHub() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub");
    REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling getHub");
    return hub;
}

void simulation::setHub(Hub *const h) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub");
    REQUIRE(h->properlyInitialised(), "hub wasn't initialised when calling setHub");
    hub = h;
}

const vector<Centrum*> &simulation::getCentra() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra");
    return centra;
}

int simulation::berekenLadingen(Centrum* centrum) const {
    REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenLadigen");
    int transport = hub->getTransport();
    int capaciteit = centrum->getCapaciteit();
    int vaccins = centrum->getVaccins();
    int voorraad = hub->getVoorraad();
    int ladingen = 0;

    //for loop met alle condities van appendix B
    // Lading verder kijken dan huidige (om na te kijken) om niet op volgende over parameters te gaan
    while ((ladingen+1)*transport <= voorraad && (ladingen+1)*transport+vaccins <= 2*capaciteit) {
        // Afbreken wanneer voldaan aan capaciteit
        if (ladingen*transport + vaccins >= capaciteit)
            break;
        ladingen += 1;
    }
    ENSURE(ladingen>=0, "berekenLadingen postconditions failed");
    return ladingen;
}

int simulation::berekenVaccinatie(Centrum* centrum){
    REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenVaccinatie");
    int result = min(centrum->getVaccins(), min(centrum->getCapaciteit(), centrum->getInwoners()-centrum->getGevaccineerd()));
    ENSURE(result>=0 && result <= centrum->getCapaciteit(), "berekenVaccinatie postconditions failed");
    return result;
}

//verlaagt het aantal vaccins in de hub met i aantal vaccins
void simulation::verlaagVaccinsHub(int vaccins){
    REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling verlaagVaccinsHub");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    int before = hub->getVoorraad();
    hub->setVoorraad(hub->getVoorraad()-vaccins);
    ENSURE(hub->getVoorraad() == before-vaccins && hub->getVoorraad() >= 0,
           "verlaagVaccinsHub postconditions failed");
}

//verhoogt de vaccins in een hub
void simulation::verhoogVaccinsHub(int vaccins) {
    REQUIRE(hub->properlyInitialised(), "hub wasn't properly initialised when calling verhoogVaccinsHub");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    hub->setVoorraad(hub->getVoorraad()+vaccins);
}

//verhoogt de vaccins in gegeven centrum met i aantal vaccins
void simulation::verhoogVaccinsCentrum(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinsCentrum");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    int oAmount = centrum->getVaccins();
    int capacity = centrum->getCapaciteit();
    centrum->setVaccins(centrum->getVaccins()+vaccins);
    ENSURE(centrum->getVaccins() == oAmount+vaccins && centrum->getVaccins() <= capacity*2,
           "verhoogVaccinsCentrum postconditions failed");
}

//verlaagt het aantal vaccins in gegeven centrum
void simulation::verlaagVaccinCentrum(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verlaagVaccinsCentrum");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    int oAmount = centrum->getVaccins();
    centrum->setVaccins(centrum->getVaccins()-vaccins);
    ENSURE(centrum->getVaccins() == oAmount-vaccins && centrum->getVaccins() >= 0,
           "verlaagVaccinsCentrum postconditions failed");
}

//verhoogt het aantal gevaccineerden in een centrum
void simulation::verhoogVaccinaties(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinaties");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
    ENSURE(centrum->getGevaccineerd() <= centrum->getInwoners(),
           "verhoogVaccinaties postconditions failed");
}

void simulation::printTransport(Centrum* centrum, int vaccins, ostream& onStream) const {
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printTransport");
    REQUIRE(vaccins >= 0, "vaccins amount can't be negative");
    REQUIRE(vaccins%hub->getTransport() == 0, "vaccins amount must be multiple of transport in hub");
    onStream << "Er werden " << vaccins/hub->getTransport() << " ladingen (" << vaccins << " vaccins)"
         << " getransporteerd naar "<< centrum->getNaam() <<"." << endl;
}

void simulation::printVaccinatie(Centrum* centrum, int vaccins, ostream& onStream) {
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printVaccinatie");
    REQUIRE(vaccins >= 0, "vaccinated amount can't be negative");
    REQUIRE(vaccins <= centrum->getCapaciteit(), "vaccinated ammount can't exceed capacity");
    onStream << "Er werden " << vaccins << " inwoners gevaccineerd in " << centrum->getNaam() << "." << endl;
}
