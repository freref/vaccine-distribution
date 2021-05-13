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

// Simulates the transport of a vaccine from a hub to a center
void autoSim::simulateTransport(Hub* hub, Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS){
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating transport");
    REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when simulating transport");
    REQUIRE(vaccins >= 0, "can't simulate transport of negative amount of vaccines");

    hub->verlaagVoorraad(vaccin, vaccins);
    c->verhoogVoorraad(vaccin, vaccins);

    if (vaccins > 0)
        c->printTransport(vaccins, vaccin, outS);
}

// Simulate transport for first injections
void autoSim::simulateEerstePrikTransport(Hub* hub, map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins,
                                          ostream& outS, int dag) {
    REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg first injection transport");
    REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd first injection transport");
    REQUIRE(dag >= 0, "can't simulate second injection transport on negative day");

    // Go over vaccines
    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        // Current hub vaccine stock distributed over the centers
        // This is done to try to deliver vaccines to every center every day (not guaranteed)
        int devide = hub->getVoorraad(vaccin) / centraHub->size();
        // Go over the centers
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

// Simulate transport for second injections
void autoSim::simulateTweedePrikTransport(Hub* hub, map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins,
                                          ostream& outS, int dag){
    REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg second injection transport");
    REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd second injection transport");
    REQUIRE(dag >= 0, "can't simulate second injection transport on negative day");

    // Go over vaccines
    for (unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++) {
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        // Go over centers
        for (map<string, Centrum*>::iterator it = centraHub->begin(); it != centraHub->end(); it++) {
            // Get necessary amount of vaccines
            int aantal = it->second->getGevac()[pair<int, Vaccine*>(dag - vaccin->getHernieuwing(), vaccin)];

            if (aantal > 0) {
                // Get amount of deliveries
                int ladingen = it->second->berekenTweedePrikLadingen(hub, vaccin, aantal);
                int v = ladingen*vaccin->getTransport();

                simulateTransport(hub, it->second, vaccin, v, outS);
            }
        }
    }
}

// Simulate first injections in a center using certain vaccine
int autoSim::simulateEerstePrik(Centrum* c, map<Vaccine*, int>::iterator it, int vaccinated, ostream& outS, int dag){
    REQUIRE(it->first->properlyInitialised(),
            "Vaccine wasn't initialised when simulating first injection");
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating first injection");
    REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people");
    REQUIRE(dag >= 0, "can't simulate second injection on negative day");

    // Get amount of people possible to vaccinate
    int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, c->getInwoners()-c->getEerste()));

    if(vaccinaties > 0){
        // Process injection
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

// Simulates the second injections in a center using a certain vaccine
int autoSim::simulateTweedePrik(map<Vaccine*, int>::iterator it, int vaccinated, Centrum* c, int dag, ostream& outS){
    REQUIRE(it->first->properlyInitialised(),
            "Vaccine wasn't initialised when simulating second injection");
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating second injection");
    REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people");
    REQUIRE(dag >= 0, "can't simulate second injection on negative day");

    // Get amount of people ready for second injection
    int aantal = c->getGevac()[pair<int, Vaccine *>(dag - it->first->getHernieuwing(), it->first)];
    // Get amount of possible second injections
    int vaccinaties = min(it->second, min(c->getCapaciteit()-vaccinated, aantal));
    // Second injections needed
    if (vaccinaties >= 0) {
        if (aantal > vaccinaties){
            // If more people need second injection than possible injections
            // Add excess amount to second injections for next day
            c->zetVaccinatie(dag - it->first->getHernieuwing()+1, it->first, aantal - vaccinaties);
        }
        // Simulate the vaccination
        c->verlaagVoorraad(it->first, vaccinaties);
        c->verhoogGevaccineerd(vaccinaties);
        if(vaccinaties > 0)
            c->printTweedeVaccinatie(vaccinaties, it->first, outS);
        if (dag - it->first->getHernieuwing() >= 0)
            // Remove pair for memory
            c->removeVaccinatie(dag - it->first->getHernieuwing(), it->first);
    }
    return vaccinaties;
}

// Simulate vaccination in a center
void autoSim::simulateVaccinatie(Centrum *c, ostream& outS, int dag) {
    REQUIRE(c->properlyInitialised(), "center wasn't initialised when calling simulateVaccinatie");
    REQUIRE(dag >= 0, "can't vaccinate on negative day");

    int vaccinated = 0; // Keep track of amount of new injections for center
    // Three stages of the vaccination simulation
    // - Firsts all second injections
    // - Then all injections with vaccines stored under 0
    // - Last all remaining injections
    for (int i = 0; i < 3; i++) {
        map<Vaccine*, int> voorraad = c->getVoorraad();
        for (map<Vaccine*, int>::iterator it = voorraad.begin(); it != voorraad.end(); it++) {
            if (i == 0)
                vaccinated += simulateTweedePrik(it, vaccinated, c, dag, outS);
            else if (i == 1 && it->first->getTemperatuur() < 0)
                vaccinated += simulateEerstePrik(c, it, vaccinated, outS, dag);
            else if (i == 2)
                vaccinated += simulateEerstePrik(c, it, vaccinated, outS, dag);
        }
    }
}

// Simulate the vaccinations for all centers
bool autoSim::simulateVaccinatieProcess(vector<Centrum*>* centra, ostream& outS, int dag){
    REQUIRE(centra->size() > unsigned (0), "No centra when simulation vaccination");
    REQUIRE(dag >= 0, "can't simulate vaccination on negative day");

    bool check = true; // Check for eveyone vaccinated
    for (long unsigned int i = 0; i < centra->size(); i++) {
        Centrum* centrum = centra->at(i);
        // Simulate vaccinations for current center
        simulateVaccinatie(centrum, outS, dag);
        if (centrum->getGevaccineerd() != centrum->getInwoners())
            check = false;
    }
    return check;
}

// Simulate delivery of vaccines to the hub
void autoSim::simulateHubDelivery(Hub* hub, simulation& s, vector<Vaccine*>* vaccins, int dag){
    REQUIRE(vaccins->size() > unsigned (0), "No vaccines in hub on delivery simulation");
    REQUIRE(dag >= 0, "can't deliver to hub on negative day");

    // Go through all vaccines
    for(unsigned int vaccinIndex = 0; vaccinIndex < vaccins->size(); vaccinIndex++){
        Vaccine* vaccin = vaccins->at(vaccinIndex);
        if(dag % (vaccin->getInterval() + 1) == 0){
            // Save the delivery
            s.addDelivery(vaccin->getType(), vaccin->getLevering());
            // Deliver to the hub
            hub->setVoorraad(vaccin, hub->getVoorraad(vaccin) + vaccin->getLevering());
        }
    }
}

// Simulate the process for amount of days
void autoSim::simulate(simulation& s, int n, ostream& outS){
    REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
    REQUIRE(n >= 0, "can't simulate negative amount of days");

    vector<Hub*> hubs = s.getHubs();
    vector<Centrum*> centra = s.getCentra();

    // Loop over days
    for(int j = 0; j < n; j++){
        outS << endl << "Dag " << j+1 << ":" << endl;
        // Loop over hubs
        for (long unsigned int i = 0; i < hubs.size(); i++){
            map<string, Centrum*> centraHub = hubs[i]->getCentra();
            vector<Vaccine*> vaccins = hubs[i]->getVaccins();

            // Simulate possible delivery to hub
            simulateHubDelivery(hubs[i], s, &vaccins, j);
            // Simulate possible deliveries from hub to centers
            // Delivery for second injections gets priority
            simulateTweedePrikTransport(hubs[i], &centraHub, &vaccins, outS, j);
            simulateEerstePrikTransport(hubs[i], &centraHub, &vaccins, outS, j);
        }
        // Simulate possible vaccinations
        if (simulateVaccinatieProcess(&centra, outS, j))
            break;
    }
}