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

//--------------------
// Transport functies
//--------------------

int simulation::berekenLadingen(Centrum* centrum, Vaccine* vaccin) const {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling berekenLadingen");
    REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenLadigen");
    int transport = vaccin->getTransport();
    int capaciteit = centrum->getCapaciteit();
    int vaccins = centrum->getVaccins();
    int voorraad = vaccin->getVoorraad();
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




void simulation::printTransport(Centrum* centrum, int vaccins, Vaccine* vaccin, ostream& onStream) const {
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printTransport");
    REQUIRE(vaccins >= 0, "vaccins amount can't be negative");
    //REQUIRE(vaccins%getHub()->getTransport() == 0, "vaccins amount must be multiple of transport in hub");
    onStream << "Er werden " << vaccins/vaccin->getTransport() << " ladingen " << vaccin->getType() << " (" << vaccins << " vaccins)"
             << " getransporteerd naar "<< centrum->getNaam() <<"." << endl;
}

//---------------------
// Vaccinatie functies
//---------------------

int simulation::berekenVaccinatie(Centrum* centrum){
    REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenVaccinatie");
    int result = min(centrum->getVaccins(), min(centrum->getCapaciteit(), centrum->getInwoners()-centrum->getGevaccineerd()));
    ENSURE(result>=0 && result <= centrum->getCapaciteit(), "berekenVaccinatie postconditions failed");
    return result;
}




//verhoogt het aantal gevaccineerden in een centrum
void simulation::verhoogVaccinaties(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinaties");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
    ENSURE(centrum->getGevaccineerd() <= centrum->getInwoners(),
           "verhoogVaccinaties postconditions failed");
}

void simulation::printVaccinatie(Centrum* centrum, int vaccins, ostream& onStream) {
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printVaccinatie");
    REQUIRE(vaccins >= 0, "vaccinated amount can't be negative");
    REQUIRE(vaccins <= centrum->getCapaciteit(), "vaccinated ammount can't exceed capacity");
    onStream << "Er werden " << vaccins << " inwoners gevaccineerd in " << centrum->getNaam() << "." << endl;
}
