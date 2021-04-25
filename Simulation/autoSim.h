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
     * \n Simulates transport of vaccines from hub to centrum
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateTransport")
     * \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateTransport")
     * @param s Simulation refrence
     * @param c Centrum pointer
     * @param outS void
     */
    static void simulateTransport(Vaccine* vaccin, simulation& s, Centrum* c, ostream& outS);
    /**
     * \n Simulates vaccine injection at centrum
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulateVaccinatie")
     * \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialized when calling simulateVaccinatie")
     * @param s Simulation refrence
     * @param c Centrum pointer
     * @param outS void
     */
    static void simulateVaccinatie(simulation& s, Centrum* c, ostream& outS, int dag);
    /**
     * \n Loop to continously simulate transport and injections
     * \n REQUIRE(s.properlyInitialised(), "simulation wasn't initialised when calling simulate");
     * \n REQUIRE(n >= 0, "can't simulate negative amount of days");
     * @param s Simulation refrence
     * @param n integer n
     * @param outS void
     */
    static void simulate(simulation& s, int n, ostream& outS);
};


#endif //PSE_AUTOSIM_H
