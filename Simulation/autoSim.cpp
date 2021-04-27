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

void autoSim::simulateTransport(Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS){
    vaccin->verlaagVaccins(vaccins);
    c->verhoogVoorraad(vaccin, vaccins);

    if (vaccins > 0)
        c->printTransport(vaccins, vaccin, outS);
}

void autoSim::simulateEerstePrikTransport(map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins, ostream& outS, int j) {
    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        int devide = centraHub->size();

        for (map<string, Centrum*>::iterator it = centraHub->begin(); it != centraHub->end(); it++) {
            //stop met 'random' vaccins te verdelen nadat iedereen een eerste prik gekregen heeft
            if (it->second->getEerste() < it->second->getInwoners()){
                int ladingen = it->second->berekenEerstePrikLadingen(vaccin, j, devide);
                int v = ladingen * vaccin->getTransport();
                simulateTransport(it->second, vaccin, v, outS);
            }
            devide -= 1;
        }
    }
}

void autoSim::simulateTweedePrikTransport(map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins, ostream& outS, int j){
    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        for (map<string, Centrum*>::iterator it = centraHub->begin(); it != centraHub->end(); it++) {
            int aantal = it->second->getGevac()[pair<int, Vaccine*>(j - vaccin->getHernieuwing(), vaccin)];

            if(aantal > 0){
                int ladingen = it->second->berekenTweedePrikLadingen(it->second, vaccin, aantal);
                int v = ladingen*vaccin->getTransport();

                simulateTransport(it->second, vaccin, v, outS);
            }
        }
    }
}

int autoSim::simulateEerstePrik(Centrum* c, map<Vaccine*, int>::iterator it, int vaccinated, ostream& outS, int dag){
    int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getEerste()));

    if(vaccinaties > 0){
        c->verlaagVoorraad(it->first, vaccinaties);
        c->zetVaccinatie(dag, it->first, vaccinaties);
        c->verhoogEerste(vaccinaties);
        c->printEersteVaccinatie(vaccinaties, it->first, outS);
    }
    return vaccinaties;
}

int autoSim::simulateTweedePrik(map<Vaccine*, int>::iterator it, int vaccinated, Centrum* c, int dag, ostream& outS){
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
    return vaccinaties;
}


void autoSim::simulateVaccinatie(Centrum *c, ostream& outS, int dag) {
    int vaccinated = 0;

    for(int i = 0; i < 3; i++){
        map<Vaccine*, int> voorraad = c->getVoorraad();
        for (map<Vaccine*, int>::iterator it = voorraad.begin(); it != voorraad.end(); it++) {
            if(i == 0)
                vaccinated += simulateTweedePrik(it, vaccinated, c, dag, outS);
            else if (i == 1 && it->first->getTemperatuur() < 0)
                vaccinated += simulateEerstePrik(c, it, vaccinated, outS, dag);
            else if (i == 2)
                vaccinated += simulateEerstePrik(c, it, vaccinated, outS, dag);
        }
    }
}

void autoSim::simulateVaccinatieProcess(vector<Centrum*>* centra, ostream& outS, int j){
    bool check = true;
    for(long unsigned int i = 0; i < centra->size(); i++){
        Centrum* centrum = centra->at(i);
        simulateVaccinatie( centrum, outS, j);
        if (centrum->getGevaccineerd() != centrum->getInwoners())
            check = false;
    }
    if(check)
        exit(0);
}

void autoSim::simulateHubDelivery(vector<Vaccine*>* vaccins, int j){
    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        if(j%(vaccin->getInterval()+1)==0){
            vaccin->setVoorraad(vaccin->getVoorraad()+vaccin->getLevering());
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
        simulateHubDelivery(&vaccins, j);
        simulateTweedePrikTransport(&centraHub, &vaccins, outS, j);
        simulateEerstePrikTransport(&centraHub, &vaccins, outS, j);
        simulateVaccinatieProcess(&centra, outS, j);
    }
}