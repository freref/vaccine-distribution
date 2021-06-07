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
    if (!hubs.empty()) {
        vector<Hub *>::iterator hIt;
        for (hIt = hubs.begin(); hIt != hubs.end(); hIt++) {
            delete *hIt;
        }
    }
    centra = vector<Centrum*>();
    hubs = vector<Hub*>();
    deliveries_by_type = map<string, int>();

    ENSURE(getCentra().empty(), "centra didn't clear correctly");
    ENSURE(getHubs().empty(), "hubs didn't clear correctly");
    ENSURE(getDeliveries().empty(), "deliveries didn't clear correctly");
}

void simulation::graphicImpression(ostream& oStream){
    REQUIRE(this->properlyInitialised(), "Simulation wasn't initialised when creating graphic impression");
    REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when creating simple impression");
    REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when creating simple impression");

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
    REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when exporting simulation");
    REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when exporting simulation");

    for(unsigned int i = 0; i < hubs.size(); i++){
        ostream << "Hub " << i+1 << " (" << hubs[i]->getTotaleVoorraad() << ")\n";
        map<string, Centrum*> cMap = hubs[i]->getCentra();
        map<string, Centrum*>::iterator cIt;
        for (cIt = cMap.begin(); cIt != cMap.end(); ++cIt) {
            ostream << "\t-> " << cIt->second->getNaam() << " (" << cIt->second->getVaccins() << " vaccins)\n";
        }
    }

    ostream << endl;

    for (long unsigned int i = 0; i < centra.size(); i++) {
        Centrum* c = centra[i];
        ostream << c->getNaam() << ": " << c->getGevaccineerd() << " gevaccineerd, nog ";
        int teGaan = c->getInwoners() - c->getGevaccineerd();
        ostream << teGaan << " inwoners niet gevaccineerd\n";
    }
}

void simulation::stats(ostream& oStream) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when exporting stats");
    REQUIRE(!getHubs().empty(), "Simulation didn't contain hubs when exporting stats");
    REQUIRE(!getCentra().empty(), "Simulation didn't contain centra when exporting stats");
    int eerste = 0;
    int tweede = 0;
    map<string, int>::iterator it;

    for (unsigned int i = 0; i < centra.size(); i++){
        eerste += centra[i]->getEerste();
        tweede += centra[i]->getGevaccineerd();
    }

    oStream << "Er zijn in totaal " << eerste-tweede << " inwoners die nog maar één vaccinatie gekregen hebben" << endl;
    oStream << "Er zijn in totaal " << tweede << " inwoners die twee vaccinaties gekregen hebben" << endl;

    for (it = deliveries_by_type.begin(); it != deliveries_by_type.end(); it++){
        oStream << "Er zijn " << it->second << " " << it->first << " vaccins geleverd" << endl;
    }
}

//------------------
// Getters, setters
//------------------

void simulation::setHubs(vector<Hub*> h) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub");
    REQUIRE(!h.empty(), "simulation must contain at least 1 hub");
    hubs = h;
    ENSURE(getHubs() == h, "setHubs postcondition failed");
}

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
    ENSURE(getCentra() == c, "setCentra postcondition failed");
}

vector<Hub*> simulation::getHubs() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub");
    return hubs;
}

const vector<Centrum*> &simulation::getCentra() const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra");
    return centra;
}

void simulation::addDelivery(string type, int aantal){
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when adding delivery");
    REQUIRE(getDeliveries()[type] + aantal >= 0, "deliveries can't go into negative");
    int oAmount = deliveries_by_type[type];
    deliveries_by_type[type] += aantal;
    ENSURE(oAmount + aantal == getDeliveries()[type], "addDelivery postcondition failed");
}

map<string, int> & simulation::getDeliveries() {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when getting deliveries");
    return deliveries_by_type;
}