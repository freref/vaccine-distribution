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
    vector<Centrum*> centra;
    Hub* hub;

    explicit autoSim(simulation* s){
        simu = s;
        hub = simu->getHub();
        centra = simu->getCentra();

        simulate();
    }
    //transport
    int berekenLadingen(Centrum* centrum);
    void verhoogVaccinsHub(int vaccins);
    void verlaagVaccinsHub(int vaccins);
    static void verhoogVaccinsCentrum(Centrum* centrum, int vaccins);
    void printTransport(Centrum* centrum, int vaccins);

    //vaccinaties
    static int berekenVaccinatie(Centrum* centrum);
    static void verlaagVaccinCentrum(Centrum* centrum, int vaccins);
    static void verhoogVaccinaties(Centrum* centrum, int vaccins);
    static void printVaccinatie(Centrum* centrum, int vaccins);

    //simulatie
    void simulate();
};


#endif //PSE_AUTOSIM_H
