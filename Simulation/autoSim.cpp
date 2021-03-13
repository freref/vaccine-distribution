//
// Created by Frederic on 12/03/2021.
//
#include <iostream>
#include "autoSim.h"
#include "Hub.h"

using namespace std;

int autoSim::berekenLadingen(Centrum* centrum) {
    int transport = hub->getTransport();
    int capaciteit = centrum->getCapaciteit();
    int vaccins = centrum->getVaccins();
    int voorraad = hub->getVoorraad();
    int ladingen;

    //for loop met alle condities van appendix B
    for(int i = transport; capaciteit > i + vaccins && i + vaccins < 2*capaciteit && transport < voorraad; i += transport){
        ladingen = i ;
    }

    return (ladingen+transport) / hub->getTransport();
}

int autoSim::berekenVaccinatie(Centrum* centrum){
    return min(centrum->getVaccins(), min(centrum->getCapaciteit(), centrum->getInwoners()-centrum->getGevaccineerd()));
}

//verlaagt het aantal vaccins in de hub met i aantal vaccins
void autoSim::verlaagVaccinsHub(int vaccins){
    hub->setVoorraad(hub->getVoorraad()-vaccins);
}

//verhoogt de vaccins in een hub
void autoSim::verhoogVaccinsHub(int vaccins) {
    hub->setVoorraad(hub->getVoorraad()+vaccins);
}

//verhoogt de vaccins in gegeven centrum met i aantal vaccins
void autoSim::verhoogVaccinsCentrum(Centrum* centrum, int vaccins){
    centrum->setVaccins(centrum->getVaccins()+vaccins);
}

//verlaagt het aantal vaccins in gegeven centrum
void autoSim::verlaagVaccinCentrum(Centrum* centrum, int vaccins){
    centrum->setVaccins(centrum->getVaccins()-vaccins);
}

//verhoogt het aantal gevaccineerden in een centrum
void autoSim::verhoogVaccinaties(Centrum* centrum, int vaccins){
    centrum->setGevaccineerd(centrum->getGevaccineerd()+vaccins);
}

void autoSim::printTransport(Centrum* centrum, int vaccins){
    cout << "Er werden " << vaccins/hub->getTransport() << " ladingen (" << vaccins << " vaccins) getransporteerd naar "<< centrum->getNaam() <<"." << endl;
}

void autoSim::printVaccinatie(Centrum* centrum, int vaccins){
    cout << "Er werden " << vaccins << " inwonders gevaccineerd in " << centrum->getNaam() << "." << endl;
}

void autoSim::simulate(){
    for(int i = 1; i < 100; i++){
        if(i%(hub->getInterval()+1) == 0)
            verhoogVaccinsHub(hub->getLevering());

        for(int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];

            if(hub->getCentra().count(centrum->getNaam())){
                int ladingen = berekenLadingen(centrum);
                int vaccins = ladingen*hub->getTransport();

                verlaagVaccinsHub(vaccins);
                verhoogVaccinsCentrum(centrum, vaccins);
                printTransport(centrum, vaccins);
            }
        }
        bool check = true;

        for(int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];

            int vaccinaties = berekenVaccinatie(centrum);
            verlaagVaccinCentrum(centrum, vaccinaties);
            verhoogVaccinaties(centrum, vaccinaties);
            printVaccinatie(centrum, vaccinaties);

            if (vaccinaties > 0)
                check = false;
        }
        if(check)
            break;
    }
}