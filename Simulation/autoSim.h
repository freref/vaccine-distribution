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
     * @param c:        Destination center
     * @param vaccin:   Vaccine to transport
     * @param vaccins:  Amount of vaccines in transport
     * @param outS:     Output stream
     */
    static void simulateTransport(Centrum* c, Vaccine* vaccin, int vaccins, ostream& outS);
    /**
     * Simulates a first injection with a vaccine
     * @param c:            Vaccination centre where injection took place
     * @param it:           Vaccine supply iterator
     * @param vaccinated:   Amount of vaccinated people
     * @param outS:         Output stream
     * @param dag:          Day of injection
     * @return
     */
    static int simulateEerstePrik(Centrum* c, map<Vaccine*, int>::iterator it, int vaccinated, ostream& outS, int dag);

    static int simulateTweedePrik(map<Vaccine*, int>::iterator it, int vaccinated, Centrum* c, int dag, ostream& outS);

    static void simulateHubDelivery(vector<Vaccine*>* vaccins, int j);

    static void simulateEerstePrikTransport(map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins, ostream& outS, int j);

    static void simulateTweedePrikTransport(map<string, Centrum*>* centraHub, vector<Vaccine*>* vaccins, ostream& outS, int j);
    /**
     * \n Simulates vaccine injection at centrum
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateVaccinatie")
     * \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateVaccinatie")
     * @param s Simulation refrence
     * @param c Centrum pointer
     * @param outS void
     */
    static void simulateVaccinatie(Centrum* c, ostream& outS, int dag);

    static bool simulateVaccinatieProcess(vector<Centrum*>* centra, ostream& outS, int j);

    /**
     * \n Loop to continously simulate transport and injections
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
     * \n REQUIRE(n >= 0, "can't simulate negative amount of days");
     * @param s:    Simulation refrence
     * @param n:    Days to simulate
     * @param outS: Output stream
     */
    static void simulate(simulation& s, int n, ostream& outS);
};


#endif //PSE_AUTOSIM_H
