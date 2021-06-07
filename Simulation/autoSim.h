/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which handles the automation of the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 1.0
 */

#ifndef PSE_AUTOSIM_H
#define PSE_AUTOSIM_H

#include <iostream>
#include "simulation.h"
#include "Centrum.h"
#include "Vaccine.h"

class autoSim {
public:
    /**
     \n Simulates the transport of a vaccine to a center
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when simulating transport")
     \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating transport")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when simulating transport")
     \n REQUIRE(vaccins >= 0, "can't simulate transport of negative amount of vaccines")
     \n REQUIRE(hub->getVoorraad(vaccin) - vaccins >= 0, "can't transport more vaccines than in stock")
     \n REQUIRE(c->getVoorraad()[vaccin] + vaccins <= c->getCapaciteit() * 2, "can't go over stock capacity in center")
     \n ENSURE((oHub - vaccins == hub->getVoorraad(vaccin)) && (oCenter + vaccins == c->getVoorraad()[vaccin]),
               "simulateTransport postcondition failed")
     * @param hub:      Hub from where to transport
     * @param c:        Destination center
     * @param vaccin:   Vaccine to transport
     * @param vaccins:  Amount of vaccines in transport
     * @param outS:     Output stream
     */
    static void simulateTransport(Hub* hub, Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS);

    /**
     \n Simulates transport for first injection vaccines
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when transporting first injectios")
     \n REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg first injection transport")
     \n REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd first injection transport")
     \n REQUIRE(dag >= 0, "can't simulate second injection transport on negative day")
     * @param hub:          Hub from where to transport
     * @param centraHub:    Map containing centra in hub
     * @param vaccins:      All vaccines in hub
     * @param transports:   Map to keep track of amount of transports per center *Output*
     * @param outS:         Output stream
     * @param dag:          Day of transport
     */
    static void simulateEerstePrikTransport(Hub *hub, map<string, Centrum *> &centraHub, vector<Vaccine *> &vaccins,
                                            map<Centrum *, int> &transports, ostream &outS, int dag);
    /**
     \n Simulates transport for second injection vaccines
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when transporting second injectios")
     \n REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg second injection transport")
     \n REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd second injection transport")
     \n REQUIRE(dag >= 0, "can't simulate second injection transport on negative day")
     * @param hub:          Hub from where to transport
     * @param centraHub:    Map containing centra in hub
     * @param vaccins:      All vaccines in hub
     * @param transports:   Map to keep track of amount of transports per center *Output*
     * @param outS:         Output stream
     * @param dag:          Day of transport
     */
    static void simulateTweedePrikTransport(Hub *hub, map<string, Centrum *> &centraHub, vector<Vaccine *> &vaccins,
                                            map<Centrum *, int> &transports, ostream &outS, int dag);

    /**
     \n Simulates a first injection with a vaccine
     \n REQUIRE(it->first->properlyInitialised(), "Vaccine wasn't initialised when simulating first injection")
     \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating first injection")
     \n REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people")
     \n REQUIRE(dag >= 0, "can't simulate second injection on negative day")
     \n ENSURE(vaccinated + vaccinaties <= c->getCapaciteit(), "can't vaccinate more people than capacity allows")
     * @param c:            Vaccination centre where injection took place
     * @param it:           Vaccine supply iterator (centrum)
     * @param vaccinated:   Amount of already vaccinated people
     * @param dag:          Day of injection
     * @param outS:         Output stream
     * @return      Amount of injections
     */
    static int simulateEerstePrik(Centrum *c, map<Vaccine *, int>::iterator it, int vaccinated, int dag, ostream &outS);
    /**
     \n Simulates a second injection with a vaccine
     \n REQUIRE(it->first->properlyInitialised(), "Vaccine wasn't initialised when simulating second injection")
     \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating second injection")
     \n REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people")
     \n REQUIRE(dag >= 0, "can't simulate second injection on negative day")
     \n ENSURE(vaccinated + vaccinaties <= c->getCapaciteit(), "can't vaccinate more people than capacity allows")
     * @param c:            Vaccination centre where injection took place
     * @param it:           Vaccine supply iterator (centrum)
     * @param vaccinated:   Amount of already vaccinated people
     * @param dag:          Day of injection
     * @param outS:         Output stream
     * @return      Amount of injections
     */
    static int simulateTweedePrik(Centrum *c, map<Vaccine *, int>::iterator it, int vaccinated, int dag, ostream &outS);

    /**
     * \n Simulates vaccine injection at centrum
     * \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when calling simulateVaccinatie")
     * \n REQUIRE(dag >= 0, "can't vaccinate on negative day")
     * @param c:    Centrum of vaccinations
     * @param dag:  Day of vaccination
     * @param outS: Output stream
     */
    static void simulateVaccinatie(Centrum *c, int dag, ostream &outS);
    /**
     \n Simulates the vaccination process
     \n REQUIRE(centra->size() > unsigned (0), "No centra when simulation vaccination")
     \n REQUIRE(dag >= 0, "can't simulate vaccination on negative day")
     * @param centra:   All centra in hub
     * @param dag:      Day of vaccination
     * @param outS:     Output stream
     * @return      bool whether everyone vaccinated in all centra
     */
    static bool simulateVaccinatieProcess(vector<Centrum *> &centra, int dag, ostream &outS);

    /**
     \n Simulates delivery to the hub
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when simulating delivery")
     \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when simulating delivery")
     \n REQUIRE(vaccins->size() > unsigned (0), "No vaccines in hub on delivery simulation")
     \n REQUIRE(dag >= 0, "can't deliver to hub on negative day")
     * @param hub:      Hub to deliver to
     * @param s:        Simulation containing hub
     * @param vaccins:  All vaccines in the hub
     * @param dag:      Day of delivery
     */
    static void simulateHubDelivery(Hub* hub, simulation& s, vector<Vaccine *> &vaccins, int dag);

    /**
     \n Loop to continously simulate transport and injections
     \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
     \n REQUIRE(n >= 0, "can't simulate negative amount of days");
     \n REQUIRE(stockDivide > 0, "stock divide must be bigger than 0")
     * @param s:                Simulation refrence
     * @param n:                Days to simulate
     * @param graphicPath:      Path to graphics output location (ending on '/')
     * @param stockDivide:      Amount of vaccine per vaccine figure in graphic output
     * @param graphicOutput:    Enable/disable graphic output
     * @param outS:             Output stream
     */
    static void simulate(simulation &s, int n, string graphicPath, int stockDivide, bool graphicOutput, ostream &outS);
};


#endif //PSE_AUTOSIM_H
