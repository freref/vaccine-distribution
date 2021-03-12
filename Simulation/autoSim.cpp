//
// Created by Frederic on 12/03/2021.
//
#include <iostream>
#include "autoSim.h"
#include "Hub.h"

using namespace std;

int autoSim::berekenLadingen(Centrum* centrum) {
    Hub* hub = simu->getHub();
    int transport = hub->getTransport();
    int capaciteit = centrum->getCapaciteit();
    int vaccins = centrum->getVaccins();
    int voorraad = hub->getVoorraad();
    int ladingen;

    //for loop met alle condities van appendix B
    for(int i = transport; capaciteit > i + vaccins && i + vaccins < 2*capaciteit && transport < voorraad; i += transport){
        cout << i << endl;
        ladingen = i ;
    }

    return (ladingen+transport) / hub->getTransport();
}

//verlaagt het aantal vaccins in de hub met i aantal vaccins
void autoSim::verlaagVaccins(int vaccins){
    Hub* hub = simu->getHub();
    hub->setVoorraad(hub->getVoorraad()-vaccins);
}

//verhoogt de vaccins in gegeven centrum met i aantal vaccins
void autoSim::verhoogVaccins(Centrum* centrum, int vaccins){
    centrum->setVaccins(centrum->getVaccins()+vaccins);
}

void autoSim::printTransport(Centrum* centrum, int vaccins){
    cout << "Er werden" << vaccins/simu->getHub()->getTransport() << "ladingen (" << vaccins << " vaccins) getransporteerd naar "<< centrum->getNaam() <<"." << endl;
}


int autoSim::berekenVaccinatie(Centrum* centrum){
    return min(centrum->getVaccins(), min(centrum->getCapaciteit(), centrum->getInwoners()-centrum->getGevaccineerd()));
}

//verlaagt het aantal vaccins in gegeven centrum
void autoSim::verlaagVaccinatie(Centrum* centrum, int vaccins){
    centrum->setVaccins(centrum->getVaccins()-vaccins);
}

//verhoogt het aantal gevaccineerden in een centrum
void autoSim::verhoogVaccinaties(Centrum* centrum, int vaccins){
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
}

void autoSim::printVaccinatie(Centrum* centrum, int vaccins){
    cout << "Er werden " << vaccins << " inwonders gevaccineerd in " << centrum->getNaam() << ".";
}

void autoSim::simulate(){

}