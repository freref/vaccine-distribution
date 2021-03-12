//
// Created by Frederic on 12/03/2021.
//
#include <iostream>
#include "autoSim.h"
#include "Hub.h"


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

void autoSim::printTransport(Centrum* centrum, int ladingen){
    std::cout << "Er werden" << ladingen << "ladingen (" << ladingen*simu->getHub()->getTransport() << " vaccins) getransporteerd naar Park Spoort Oost." << endl;
}

void autoSim::simulate(){

}