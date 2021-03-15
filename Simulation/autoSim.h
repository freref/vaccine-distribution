/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class which handles the automation of the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 1.0
 */

#ifndef PSE_AUTOSIM_H
#define PSE_AUTOSIM_H
#include "simulation.h"
#include "Centrum.h"


class autoSim {
public:
    simulation* simu;
    vector<Centrum*> centra;
    Hub* hub;

    explicit autoSim(simulation* s, int n){
        simu = s;
        hub = simu->getHub();
        centra = simu->getCentra();

        simulate(n);
    }
    //transport
    int berekenLadingen(Centrum* centrum) const;
    void verhoogVaccinsHub(int vaccins);
    void verlaagVaccinsHub(int vaccins);
    static void verhoogVaccinsCentrum(Centrum* centrum, int vaccins);
    void printTransport(Centrum* centrum, int vaccins) const;

    //vaccinaties
    static int berekenVaccinatie(Centrum* centrum);
    static void verlaagVaccinCentrum(Centrum* centrum, int vaccins);
    static void verhoogVaccinaties(Centrum* centrum, int vaccins);
    static void printVaccinatie(Centrum* centrum, int vaccins);

    //simulatie
    void simulate(unsigned int n);
};


#endif //PSE_AUTOSIM_H
