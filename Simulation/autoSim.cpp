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

void autoSim::simulateTransport(Hub* hub, Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS){
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating transport");
    REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when simulating transport");
    REQUIRE(vaccins >= 0, "can't simulate transport of negative amount of vaccines");

    hub->verlaagVoorraad(vaccin, vaccins);
    c->verhoogVoorraad(vaccin, vaccins);

    if (vaccins > 0)
        c->printTransport(vaccins, vaccin, outS);
}

void autoSim::simulateEerstePrikTransport(Hub* hub, map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins,
                                          ostream& outS, int dag) {
    REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg first injection transport");
    REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd first injection transport");
    REQUIRE(dag >= 0, "can't simulate second injection transport on negative day");

    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        int devide = hub->getVoorraad(vaccin) / centraHub->size();

        for (map<string, Centrum*>::iterator it = centraHub->begin(); it != centraHub->end(); it++) {
            //stop met 'random' vaccins te verdelen nadat iedereen een eerste prik gekregen heeft
            if (it->second->getEerste() < it->second->getInwoners()){
                int ladingen = it->second->berekenEerstePrikLadingen(hub, vaccin, dag, devide);
                int v = ladingen * vaccin->getTransport();
                simulateTransport(hub, it->second, vaccin, v, outS);
            }
//            devide -= 1;
        }
    }
}

void autoSim::simulateTweedePrikTransport(Hub* hub, map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins,
                                          ostream& outS, int dag){
    REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg second injection transport");
    REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd second injection transport");
    REQUIRE(dag >= 0, "can't simulate second injection transport on negative day");

    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        for (map<string, Centrum*>::iterator it = centraHub->begin(); it != centraHub->end(); it++) {
            int aantal = it->second->getGevac()[pair<int, Vaccine*>(dag - vaccin->getHernieuwing(), vaccin)];

            if(aantal > 0){
                int ladingen = it->second->berekenTweedePrikLadingen(hub, vaccin, aantal);
                int v = ladingen*vaccin->getTransport();

                simulateTransport(hub, it->second, vaccin, v, outS);
            }
        }
    }
}

int autoSim::simulateEerstePrik(Centrum* c, map<Vaccine*, int>::iterator it, int vaccinated, ostream& outS, int dag){
    REQUIRE(it->first->properlyInitialised(),
            "Vaccine wasn't initialised when simulating first injection");
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating first injection");
    REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people");
    REQUIRE(dag >= 0, "can't simulate second injection on negative day");

    int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getEerste()));

    if(vaccinaties > 0){
        c->verlaagVoorraad(it->first, vaccinaties);
        c->zetVaccinatie(dag, it->first, vaccinaties);
        c->verhoogEerste(vaccinaties);
        c->printEersteVaccinatie(vaccinaties, it->first, outS);
        if (it->first->getHernieuwing() == 0) {
            c->verhoogGevaccineerd(vaccinaties);
        }
    }
    return vaccinaties;
}

int autoSim::simulateTweedePrik(map<Vaccine*, int>::iterator it, int vaccinated, Centrum* c, int dag, ostream& outS){
    REQUIRE(it->first->properlyInitialised(),
            "Vaccine wasn't initialised when simulating second injection");
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating second injection");
    REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people");
    REQUIRE(dag >= 0, "can't simulate second injection on negative day");

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
        if (dag - it->first->getHernieuwing() >= 0)
            c->removeVaccinatie(dag - it->first->getHernieuwing(), it->first);
    }
    return vaccinaties;
}


void autoSim::simulateVaccinatie(Centrum *c, ostream& outS, int dag) {
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when calling simulateVaccinatie");
    REQUIRE(dag >= 0, "can't vaccinate on negative day");

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

bool autoSim::simulateVaccinatieProcess(vector<Centrum*>* centra, ostream& outS, int dag){
    REQUIRE(centra->size() > unsigned (0), "No centra when simulation vaccination");
    REQUIRE(dag >= 0, "can't simulate vaccination on negative day");

    bool check = true;
    for(long unsigned int i = 0; i < centra->size(); i++){
        Centrum* centrum = centra->at(i);
        simulateVaccinatie(centrum, outS, dag);
        if (centrum->getGevaccineerd() != centrum->getInwoners())
            check = false;
    }
    return check;
}

void autoSim::simulateHubDelivery(Hub* hub, simulation& s, vector<Vaccine*>* vaccins, int dag){
    REQUIRE(vaccins->size() > unsigned (0), "No vaccines in hub on delivery simulation");
    REQUIRE(dag >= 0, "can't deliver to hub on negative day");

    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        if(dag % (vaccin->getInterval() + 1) == 0){
            s.addDelivery(vaccin->getType(), vaccin->getLevering());
            hub->setVoorraad(vaccin, hub->getVoorraad(vaccin) + vaccin->getLevering());
        }
    }
}

void autoSim::simulate(simulation& s, int n, ostream& outS){
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");

    vector<Hub*> hubs = s.getHubs();
    vector<Centrum*> centra = s.getCentra();

    for(int j = 0; j < n; j++){
        outS << endl << "Dag " << j+1 << ":" << endl;
        for (long unsigned int i = 0; i < hubs.size(); i++){
            map<string, Centrum*> centraHub = hubs[i]->getCentra();
            vector<Vaccine*> vaccins = hubs[i]->getVaccins();

            simulateHubDelivery(hubs[i], s, &vaccins, j);
            simulateTweedePrikTransport(hubs[i], &centraHub, &vaccins, outS, j);
            simulateEerstePrikTransport(hubs[i], &centraHub, &vaccins, outS, j);
        }
        if (simulateVaccinatieProcess(&centra, outS, j))
            break;
    }
}