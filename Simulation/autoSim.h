//
// Created by Frederic on 12/03/2021.
//

#ifndef PSE_AUTOSIM_H
#define PSE_AUTOSIM_H
#include "simulation.h"
#include "Centrum.h"


class autoSim {
public:
    simulation* simu;

    autoSim(simulation* s){
        simu = s;
        simulate();
    }
    //transport
    int berekenLadingen(Centrum* centrum);
    void verlaagVaccins(int vaccins);
    void verhoogVaccins(Centrum* centrum, int vaccins);
    void printTransport(Centrum* centrum, int vaccins);

    //vaccinaties
    int berekenVaccinatie(Centrum* centrum);
    void verlaagVaccinatie(Centrum* centrum, int vaccins);
    void verhoogVaccinaties(Centrum* centrum, int vaccins);
    void printVaccinatie(Centrum* centrum, int vaccins);

    //simulatie
    void simulate();
};


#endif //PSE_AUTOSIM_H
