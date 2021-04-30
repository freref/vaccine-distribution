/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the simulation class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 2.0
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
    if (!centra.empty()) {
        vector<Centrum *>::iterator cIt;
        for (cIt = centra.begin(); cIt != centra.end(); cIt++) {
            delete *cIt;
        }
    }
    centra = vector<Centrum*>();
}

void simulation::graphicImpression(ostream& oStream){
    REQUIRE(this->properlyInitialised(), "Simulation wasn't initialised when creating graphic impression");
//    ofstream MyFile("../graphic_impression.txt");
    string output;

    for(unsigned int i = 0; i < centra.size(); i++){
        oStream << centra[i]->getNaam() + ":\n\t- vaccins\t\t[";
        int vaccins = centra[i]->getVaccins()*100/(centra[i]->getCapaciteit() * 2);

        for(int idx = 1; idx <= 20; idx++){
            if(idx <= vaccins/5)
                oStream << "=";
            else
                oStream << " ";
        }

        oStream << "] ";
        oStream << vaccins;
        oStream << "%";
        oStream << "\n\t- gevaccineerd\t[";
        int gevaccineerd = centra[i]->getGevaccineerd()*100/centra[i]->getInwoners();

        for(int idx = 1; idx <= 20; idx++){
            if(idx <= gevaccineerd/5)
                oStream << "=";
            else
                oStream << " ";
        }

        oStream << "] ";
        oStream << gevaccineerd;
        oStream << "%";
        oStream << "\n";
    }
}

void simulation::exportSim(ostream &ostream) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling exporter");
    for(int i = 0; i < hubs.size(); i++){
        ostream << "Hub " << to_string(i+1) << " (" << hubs[i]->getTotaleVoorraad() << ")\n";
    }
    for (long unsigned int i = 0; i < centra.size(); i++){
        ostream << "\t-> " << centra[i]->getNaam() << " (" << centra[i]->getVaccins() << " vaccins" << ")\n";
    }
    ostream << endl;
    for (long unsigned int i = 0; i < centra.size(); i++) {
        Centrum* c = centra[i];
        ostream << c->getNaam() << ": " << c->getGevaccineerd() << " gevaccineerd, nog ";
        int teGaan = c->getInwoners() - c->getGevaccineerd();
        ostream << teGaan << " inwoners niet gevaccineerd\n";
    }
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

vector<Hub*> simulation::getHubs() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub");
    return hubs;
}

void simulation::setHubs(vector<Hub*> h) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub");
    hubs = h;
}

const vector<Centrum*> &simulation::getCentra() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra");
    return centra;
}

void simulation::stats(ostream& oStream){
    int eerste = 0;
    int tweede = 0;
    map<string, int>::iterator it;

    for (int i = 0; i < centra.size(); i++){
        eerste += centra[i]->getEerste();
        tweede += centra[i]->getGevaccineerd();
    }

    oStream << "Er zijn in het totaal " << eerste-tweede << " inwoners die nog maar één vaccinatie gekregen hebben" << endl;
    oStream << "Er zijn in het totaal " << tweede << " inwoners die twee vaccinaties gekregen hebben" << endl;

    for (it = deliveries_by_type.begin(); it != deliveries_by_type.end(); it++){
        oStream << "Er zijn " << it->second << " " << it->first << " vaccins geleverd" << endl;
    }
}

void simulation::addDelivery(string type, int aantal){
    deliveries_by_type[type] += aantal;
}