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

void autoSim::simulateTransport(Vaccine* vaccin, Centrum *c, ostream& outS, int dag, int devide) {
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateTransport");

    int ladingen = c->berekenLadingen(vaccin, dag, devide);
    int vaccins = ladingen * vaccin->getTransport();

    vaccin->verlaagVaccins(vaccins);
    c->verhoogVoorraad(vaccin, vaccins);

    if (vaccins > 0)
        c->printTransport(vaccins, vaccin, outS);
}

void autoSim::simulateTweedePrikTransport(Vaccine* vaccin, Centrum* c, ostream& outS, int aantal){
    int vaccins = min(aantal, min(vaccin->getVoorraad(), c->getCapaciteit()*2 - c->getVaccins()));

    int ladingen = vaccins/vaccin->getTransport();
    if (vaccins > 0 && ladingen == 0)
        ladingen = 1;

    vaccins = ladingen*vaccin->getTransport();

    vaccin->verlaagVaccins(vaccins);
    c->verhoogVoorraad(vaccin, vaccins);
    if (vaccins > 0)
        c->printTransport(vaccins, vaccin, outS);
}

void autoSim::simulateVaccinatie(simulation &s, Centrum *c, ostream& outS, int dag) {
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateVaccinatie");
    REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateVaccinatie");

    map<Vaccine*, int> voorraad1 = c->getVoorraad();
    //tweede prik voorrang
    int vaccinated = 0;
    for (map<Vaccine*, int>::iterator it = voorraad1.begin(); it != voorraad1.end(); it++) {
        int aantal = c->getGevac()[pair<int, Vaccine *>(dag - it->first->getHernieuwing(), it->first)];
        int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, aantal));
        if (vaccinaties >= 0) {
            if (aantal > vaccinaties){
                c->zetVaccinatie(dag - it->first->getHernieuwing()+1, it->first, aantal - vaccinaties);
            }

            c->verlaagVoorraad(it->first, vaccinaties);
            c->verhoogGevaccineerd(vaccinaties);
            if(vaccinaties > 0)
                c->printTweedeVaccinatie(vaccinaties, it->first, outS);
        }
    }

    //zet eerste de vaccins die koel bewaard moeten blijven
    map<Vaccine*, int> voorraad2 = c->getVoorraad();

    for (map<Vaccine*, int>::iterator it = voorraad2.begin(); it != voorraad2.end(); it++) {
        if(it->first->getTemperatuur() < 0){
            int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getEerste()));
            vaccinated += vaccinaties;

            if(vaccinaties > 0){
                c->verlaagVoorraad(it->first, vaccinaties);
                c->zetVaccinatie(dag, it->first, vaccinaties);
                c->verhoogEerste(vaccinaties);
                c->printEersteVaccinatie(vaccinaties, it->first, outS);
            }
        }
    }

    map<Vaccine*, int> voorraad3 = c->getVoorraad();
    for (map<Vaccine*, int>::iterator it = voorraad3.begin(); it != voorraad3.end(); it++) {
        int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getEerste()));
        vaccinated += vaccinaties;

        if(vaccinaties > 0){
            c->verlaagVoorraad(it->first, vaccinaties);
            c->zetVaccinatie(dag, it->first, vaccinaties);
            c->verhoogEerste(vaccinaties);
            c->printEersteVaccinatie(vaccinaties, it->first, outS);
        }
    }
}

void autoSim::simulate(simulation& s, int n, ostream& outS){
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");
    Hub* hub = s.getHub();
    map<string, Centrum*> centraHub = hub->getCentra();
    vector<Centrum*> centra = s.getCentra();
    vector<Vaccine*> vaccins = hub->getVaccins();

    for(int j = 0; j < n+1; j++){
        cout << endl << "Dag " << j+1 << ":" << endl;
        for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins.size(); vaccinIndex++){
            Vaccine* vaccin = vaccins[vaccinIndex];
            if(j%(vaccin->getInterval()+1)==0){
                vaccin->setVoorraad(vaccin->getVoorraad()+vaccin->getLevering());
            }
            //slimme verdeling voorrang aan de 2de prikken
            for (map<string, Centrum*>::iterator it = centraHub.begin(); it != centraHub.end(); it++) {
                int aantal = it->second->getGevac()[pair<int, Vaccine*>(j - vaccin->getHernieuwing(), vaccin)];

                if(aantal > 0){
                    simulateTweedePrikTransport(vaccin, it->second, outS, aantal);
                }
            }
        }

        for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins.size(); vaccinIndex++){
            Vaccine* vaccin = vaccins[vaccinIndex];
            int devide = s.getCentra().size();

            for (map<string, Centrum*>::iterator it = centraHub.begin(); it != centraHub.end(); it++) {
                //stop met 'random' vaccins te verdelen nadat iedereen een eerste prik gekregen heeft
                if (it->second->getEerste() < it->second->getInwoners())
                    simulateTransport(vaccin, it->second, outS, j, devide);
                devide -= 1;
            }
        }

        bool check = true;
        for(long unsigned int i = 0; i < centra.size(); i++){
            Centrum* centrum = centra[i];
            simulateVaccinatie(s, centrum, outS, j);
            if (centrum->getGevaccineerd() != centrum->getInwoners())
                check = false;
        }
        if(check)
            break;
    }
}