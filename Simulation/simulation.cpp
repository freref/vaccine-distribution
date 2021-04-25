/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the simulation class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#include <iostream>
#include <fstream>
#include "simulation.h"
#include "Centrum.h"
#include "Hub.h"
#include "DesignByContract.h"

//----------------------------------
// Constructors, Destructor, checks
//----------------------------------

simulation::simulation() {
    _initCheck = this;
    hub = NULL;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

simulation::~simulation() {
    clear();
    _initCheck = NULL;
}

bool simulation::properlyInitialised() const {
    return _initCheck == this;
}

void simulation::clear() {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling clear");
    if (hub)
        delete hub;
    hub = NULL;
    if (!centra.empty()) {
        vector<Centrum *>::iterator cIt;
        for (cIt = centra.begin(); cIt != centra.end(); cIt++) {
            delete *cIt;
        }
    }
    centra = vector<Centrum*>();
    ENSURE(getHub() == NULL && getCentra().empty(), "clear postconditions failed");
}

void simulation::graphicImpression(){
    ofstream MyFile("../graphic_impression.txt");
    string output;

    for(int i = 0; i < centra.size(); i++){
        MyFile << centra[i]->getNaam() + ":\n\t- vaccins\t\t[";
        int vaccins = centra[i]->getVaccins()*100/centra[i]->getCapaciteit();

        for(int idx = 1; idx <= 20; idx++){
            if(idx <= vaccins/5)
                MyFile << "=";
            else
                MyFile << " ";
        }

        MyFile << "]"+to_string(vaccins)+"%";
        MyFile << "\n\t- gevaccineerd\t[";
        int gevaccineerd = centra[i]->getGevaccineerd()*100/centra[i]->getInwoners();

        for(int idx = 1; idx <= 20; idx++){
            if(idx <= gevaccineerd/5)
                MyFile << "=";
            else
                MyFile << " ";
        }

        MyFile << "]"+to_string(gevaccineerd)+"%";
        MyFile << "\n";
    }
    MyFile.close();
}

//------------------
// Getters, setters
//------------------

void simulation::addCentrum(Centrum* c) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling addCentrum");
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialised when calling addCentrum");
    long unsigned int oSize = centra.size();
    centra.push_back(c);
    ENSURE(getCentra().size() == oSize+1, "addCentrum postconditions failed");
}

void simulation::setCentra(const vector<Centrum *> &c) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setCentra");
    REQUIRE(!c.empty(), "simulations must contain at least 1 centrum");
    centra = c;
    ENSURE(getCentra().size() == c.size(), "setCentra postcondition failed");
}

Hub* simulation::getHub() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub");
    return hub;
}

void simulation::setHub(Hub *const h) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub");
    REQUIRE(h->properlyInitialised(), "hub wasn't initialised when calling setHub");
    hub = h;
    ENSURE(getHub() == h, "setHub postconditions failed");
}

const vector<Centrum*> &simulation::getCentra() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra");
    return centra;
}

//verhoogt het aantal gevaccineerden in een centrum
void simulation::verhoogVaccinaties(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinaties");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
    ENSURE(centrum->getGevaccineerd() <= centrum->getInwoners(),
           "verhoogVaccinaties postconditions failed");
}

void simulation::exportSim(ostream &ostream) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling exporter");
    ostream << "Hub (" << hub->accessorTotaleVoorraad() << ")\n";
    map<string, Centrum*> hCentra = hub->getCentra();
    for (map<string, Centrum*>::iterator it = hCentra.begin(); it != hCentra.end(); it++) {
        ostream << "\t-> " << it->second->getNaam() << " (" << it->second->getVaccins() << " vaccins" << ")\n";
    }
    ostream << endl;
    for (long unsigned int i = 0; i < centra.size(); i++) {
        Centrum* c = centra[i];
        ostream << c->getNaam() << ": " << c->getGevaccineerd() << " gevaccineerd, nog ";
        int teGaan = c->getInwoners() - c->getGevaccineerd();
        ostream << teGaan << " inwoners niet gevaccineerd\n";
    }
}