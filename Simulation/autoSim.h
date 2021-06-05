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
     \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating transport")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when simulating transport")
     \n REQUIRE(vaccins >= 0, "can't simulate transport of negative amount of vaccines")
     * @param c:        Destination center
     * @param vaccin:   Vaccine to transport
     * @param vaccins:  Amount of vaccines in transport
     * @param outS:     Output stream
     */
    static void simulateTransport(Hub* hub, Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS);

    /**
     \n Simulates transport for first injection vaccines
     \n REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg first injection transport")
     \n REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd first injection transport")
     \n REQUIRE(dag >= 0, "can't simulate second injection transport on negative day")
     * @param centraHub:    Map containing centra in hub
     * @param vaccins:      All vaccines in hub
     * @param outS:         Output stream
     * @param dag:          Day of transport
     */
    static void simulateEerstePrikTransport(Hub *hub, map<string, Centrum *> &centraHub, vector<Vaccine *> &vaccins,
                                            map<Centrum *, int> &transports, ostream &outS, int dag);
    /**
     \n Simulates transport for second injection vaccines
     \n REQUIRE(centraHub->size() > unsigned (0), "no centra when simulationg second injection transport")
     \n REQUIRE(vaccins->size() > unsigned (0), "no vaccines when simulationd second injection transport")
     \n REQUIRE(dag >= 0, "can't simulate second injection transport on negative day")
     * @param centraHub:    Map containing centra in hub
     * @param vaccins:      All vaccines in hub
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
     * @param c:            Vaccination centre where injection took place
     * @param it:           Vaccine supply iterator (centrum)
     * @param vaccinated:   Amount of already vaccinated people
     * @param outS:         Output stream
     * @param dag:          Day of injection
     * @return      Amount of injections
     */
    static int simulateEerstePrik(Centrum* c, map<Vaccine*, int>::iterator it, int vaccinated, ostream& outS, int dag);
    /**
     \n Simulates a second injection with a vaccine
     \n REQUIRE(it->first->properlyInitialised(), "Vaccine wasn't initialised when simulating second injection")
     \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when simulating second injection")
     \n REQUIRE(vaccinated >= 0, "can't have negative amount of already vaccinated people")
     \n REQUIRE(dag >= 0, "can't simulate second injection on negative day")
     * @param it:           Vaccine supply iterator (centrum)
     * @param vaccinated:   Amount of already vaccinated people
     * @param c:            Vaccination center
     * @param dag:          Day of injection
     * @param outS:         Output stream
     * @return      Amount of injections
     */
    static int simulateTweedePrik(map<Vaccine*, int>::iterator it, int vaccinated, Centrum* c, int dag, ostream& outS);

    /**
     * \n Simulates vaccine injection at centrum
     * \n REQUIRE(c->properlyInitialised(), "center wasn't initialised when calling simulateVaccinatie")
     * \n REQUIRE(dag >= 0, "can't vaccinate on negative day")
     * @param c:    Centrum of vaccinations
     * @param outS: Output stream
     * @param dag:  Day of vaccination
     */
    static void simulateVaccinatie(Centrum* c, ostream& outS, int dag);
    /**
     \n Simulates the vaccination process
     \n REQUIRE(centra->size() > unsigned (0), "No centra when simulation vaccination")
     \n REQUIRE(dag >= 0, "can't simulate vaccination on negative day")
     * @param centra:   All centra in hub
     * @param outS:     Output stream
     * @param dag:      Day of vaccinations
     * @return      bool whether everyone vaccinated in all centra
     */
    static bool simulateVaccinatieProcess(vector<Centrum *> &centra, ostream& outS, int dag);

    /**
     \n Simulates delivery to the hub
     \n REQUIRE(vaccins->size() > unsigned (0), "No vaccines in hub on delivery simulation")
     \n REQUIRE(dag >= 0, "can't deliver to hub on negative day")
     * @param vaccins:  All vaccines in the hub
     * @param dag:      Day of delivery
     */
    static void simulateHubDelivery(Hub* hub, simulation& s, vector<Vaccine *> &vaccins, int dag);

    /**
     * \n Loop to continously simulate transport and injections
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
     * \n REQUIRE(n >= 0, "can't simulate negative amount of days");
     * @param s:    Simulation refrence
     * @param n:    Days to simulate
     * @param outS: Output stream
     */
    static void simulate(simulation &s, int n, string graphicPath, bool graphicOutput, ostream &outS);
};


#endif //PSE_AUTOSIM_H
