/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the autoSim class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 2.0
 */

#include <iostream>
#include "autoSim.h"
#include "Hub.h"
#include "DesignByContract.h"

using namespace std;

void autoSim::simulateTransport(Vaccine* vaccin, simulation &s, Centrum *c, ostream& outS) {
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateTransport");
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateTransport");

    int ladingen = s.berekenLadingen(c, vaccin);
    int vaccins = ladingen * vaccin->getTransport();

    vaccin->verlaagVaccins(vaccins);
    c->verhoogVoorraad(vaccin, vaccins);

    if (vaccins > 0)
        s.printTransport(c, vaccins, vaccin, outS);
}

void autoSim::simulateVaccinatie(simulation &s, Centrum *c, ostream& outS) {
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateVaccinatie");
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateVaccinatie");

    map<Vaccine*, int> voorraad = c->getVoorraad();
    int vaccinated = 0;
    for (map<Vaccine*, int>::iterator it = voorraad.begin(); it != voorraad.end(); it++) {
        int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getGevaccineerd()));
        vaccinated += vaccinaties;
        c->verlaagVoorraad(it->first, vaccinaties);
        s.verhoogVaccinaties(c, vaccinaties);
        if(vaccinaties > 0)
            cout << "Er werden " << vaccinaties << " inwoners gevaccineerd in " << c->getNaam() << " met het "<< it->first->getType()<<" vaccin." << endl;
    }
}

void autoSim::simulate(simulation& s, int n, ostream& outS){
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");
    Hub* hub = s.getHub();
    map<string, Centrum*> centraHub = hub->getCentra();
    vector<Centrum*> centra = s.getCentra();
    vector<Vaccine*> vaccins = hub->getVaccins();

    for(int j = 1; j < n+1; j++){
        for(int vaccinIndex = 0; vaccinIndex < vaccins.size(); vaccinIndex++){
            Vaccine* vaccin = vaccins[vaccinIndex];
            if(j%(vaccin->getInterval()+1)==0){
                vaccin->setVoorraad(vaccin->getVoorraad()+vaccin->getLevering());
            }
            for (map<string, Centrum*>::iterator it = centraHub.begin(); it != centraHub.end(); it++) {
                simulateTransport(vaccin, s, it->second, outS);
            }
        }
        bool check = true;
        for(long unsigned int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];
            simulateVaccinatie(s, centrum, outS);
            if (centrum->getGevaccineerd() != centrum->getInwoners())
                check = false;
        }
        cout << endl;
        if(check)
            break;
    }
}