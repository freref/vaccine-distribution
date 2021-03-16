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
#include "DesignByContract.h"

using namespace std;

void autoSim::simulateTransport(simulation &s, Centrum *c, ostream& outS) {
    Hub* h = s.getHub();
    int ladingen = s.berekenLadingen(c);
    int vaccins = ladingen*h->getTransport();

    s.verlaagVaccinsHub(vaccins);
    s.verhoogVaccinsCentrum(c, vaccins);
    s.printTransport(c, vaccins, outS);
}

void autoSim::simulateVaccinatie(simulation &s, Centrum *c, ostream& outS) {
    int vaccinaties = s.berekenVaccinatie(c);
    s.verlaagVaccinCentrum(c, vaccinaties);
    s.verhoogVaccinaties(c, vaccinaties);
    s.printVaccinatie(c, vaccinaties, outS);
    // cout << vaccinaties << "\t -> " << centrum->getVaccins() << endl; // DEBUG INFO
}

void autoSim::simulate(simulation& s, int n, ostream& outS){
    // REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling simulate");
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");
    Hub* hub = s.getHub();
    map<string, Centrum*> centraHub = hub->getCentra();
    vector<Centrum*> centra = s.getCentra();
    for(int j = 1; j < n+1; j++){
//        cout << endl << "DAG: " << j << endl;               // DEBUG INFO
//        cout << "Hub: " << hub->getVoorraad() << "\t-> ";   // DEBUG INFO
        if(j%(hub->getInterval()+1) == 0)
            s.verhoogVaccinsHub(hub->getLevering());
//        cout << hub->getVoorraad() << endl;                 // DEBUG INFO
        // Transporten uitvoeren
        for (map<string, Centrum*>::iterator it = centraHub.begin(); it != centraHub.end(); it++) {
//            int before = it->second->getVaccins();          // DEBUG INFO
            simulateTransport(s, it->second, outS);
//            cout << "Centrum: " << before << "\t -> " << it->second->getVaccins() << endl; // DEBUG INFO
        }
//        for(int i = 0; i < centra.size(); i++){
//            Centrum* centrum = centra[i];
//
//            if(hub->getCentra().count(centrum->getNaam())){
//                int ladingen = berekenLadingen(centrum);
//                int vaccins = ladingen*hub->getTransport();
//
//                verlaagVaccinsHub(vaccins);
//                verhoogVaccinsCentrum(centrum, vaccins);
//                printTransport(centrum, vaccins);
//            }
//        }
        bool check = true;
        // Vaccinaties uitvoeren
        for(long unsigned int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];
//            int beforeV = centrum->getVaccins();            // DEBUG INFO
            simulateVaccinatie(s, centrum, outS);
//            cout << "Centrum: " << beforeV << "\t-> " << centrum->getVaccins() << endl; // DEBUG INFO

//            int vaccinaties = berekenVaccinatie(centrum);
//            verlaagVaccinCentrum(centrum, vaccinaties);
//            verhoogVaccinaties(centrum, vaccinaties);
//            printVaccinatie(centrum, vaccinaties);

            if (centrum->getGevaccineerd() != centrum->getInwoners())
                check = false;
        }
        if(check)
            break;
    }
}