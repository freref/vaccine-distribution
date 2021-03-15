/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the autoSim class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 1.0
 */

#include <iostream>
#include "autoSim.h"
#include "Hub.h"
#include "../DesignByContract.h"

using namespace std;

int autoSim::berekenLadingen(Centrum* centrum) const {
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

int autoSim::berekenVaccinatie(Centrum* centrum){
    REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenVaccinatie");
    int result = min(centrum->getVaccins(), min(centrum->getCapaciteit(), centrum->getInwoners()-centrum->getGevaccineerd()));
    ENSURE(result>=0 && result <= centrum->getCapaciteit(), "berekenVaccinatie postconditions failed");
    return result;
}

//verlaagt het aantal vaccins in de hub met i aantal vaccins
void autoSim::verlaagVaccinsHub(int vaccins){
    REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling verlaagVaccinsHub");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    int before = hub->getVoorraad();
    hub->setVoorraad(hub->getVoorraad()-vaccins);
    ENSURE(hub->getVoorraad() == before-vaccins && hub->getVoorraad() >= 0,
           "verlaagVaccinsHub postconditions failed");
}

//verhoogt de vaccins in een hub
void autoSim::verhoogVaccinsHub(int vaccins) {
    REQUIRE(hub->properlyInitialised(), "hub wasn't properly initialised when calling verhoogVaccinsHub");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    hub->setVoorraad(hub->getVoorraad()+vaccins);
}

//verhoogt de vaccins in gegeven centrum met i aantal vaccins
void autoSim::verhoogVaccinsCentrum(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinsCentrum");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    int oAmount = centrum->getVaccins();
    int capacity = centrum->getCapaciteit();
    centrum->setVaccins(centrum->getVaccins()+vaccins);
    ENSURE(centrum->getVaccins() == oAmount+vaccins && centrum->getVaccins() <= capacity*2,
           "verhoogVaccinsCentrum postconditions failed");
}

//verlaagt het aantal vaccins in gegeven centrum
void autoSim::verlaagVaccinCentrum(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verlaagVaccinsCentrum");
    REQUIRE(vaccins>=0, "vaccins amount must be positive");
    int oAmount = centrum->getVaccins();
    centrum->setVaccins(centrum->getVaccins()-vaccins);
    ENSURE(centrum->getVaccins() == oAmount-vaccins && centrum->getVaccins() >= 0,
           "verlaagVaccinsCentrum postconditions failed");
}

//verhoogt het aantal gevaccineerden in een centrum
void autoSim::verhoogVaccinaties(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinaties");
    REQUIRE(vaccins >= 0, "vaccins amount must be positive");
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
    ENSURE(centrum->getGevaccineerd() <= centrum->getInwoners(),
           "verhoogVaccinaties postconditions failed");
}

void autoSim::printTransport(Centrum* centrum, int vaccins) const {
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printTransport");
    REQUIRE(vaccins >= 0, "vaccins amount can't be negative");
    REQUIRE(vaccins%hub->getTransport() == 0, "vaccins amount must be multiple of transport in hub");
    cout << "Er werden " << vaccins/hub->getTransport() << " ladingen (" << vaccins << " vaccins)"
        << " getransporteerd naar "<< centrum->getNaam() <<"." << endl;
}

void autoSim::printVaccinatie(Centrum* centrum, int vaccins){
    REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printVaccinatie");
    REQUIRE(vaccins >= 0, "vaccinated amount can't be negative");
    REQUIRE(vaccins <= centrum->getCapaciteit(), "vaccinated ammount can't exceed capacity");
    cout << "Er werden " << vaccins << " inwoners gevaccineerd in " << centrum->getNaam() << "." << endl;
}

void autoSim::simulate(unsigned int n){
    REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling simulate");
    REQUIRE(simu->properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");
    for(int j = 1; j < n+1; j++){
        // cout << endl << "DAG: " << j << endl; // DEBUG INFO
        if(j%(hub->getInterval()+1) == 0)
            verhoogVaccinsHub(hub->getLevering());
        // Transporten uitvoeren
        for(int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];

            if(hub->getCentra().count(centrum->getNaam())){
                int ladingen = berekenLadingen(centrum);
                int vaccins = ladingen*hub->getTransport();

                verlaagVaccinsHub(vaccins);
                verhoogVaccinsCentrum(centrum, vaccins);
                printTransport(centrum, vaccins);
                // cout << centrum->getCapaciteit() << ":\t" << centrum->getVaccins() << endl; // DEBUG INFO
            }
        }
        bool check = true;
        // Vaccinaties uitvoeren
        for(int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];

            int vaccinaties = berekenVaccinatie(centrum);
            verlaagVaccinCentrum(centrum, vaccinaties);
            verhoogVaccinaties(centrum, vaccinaties);
            printVaccinatie(centrum, vaccinaties);
            // cout << vaccinaties << "\t -> " << centrum->getVaccins() << endl; // DEBUG INFO

            if (centrum->getGevaccineerd() != centrum->getInwoners())
                check = false;
        }
        if(check)
            break;
    }
}