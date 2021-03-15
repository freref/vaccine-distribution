/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class which handles the automation of the simulation
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

class autoSim {
public:
    //simulatie
    static void simulateTransport(simulation& s, Centrum* c, ostream& outS);
    static void simulateVaccinatie(simulation& s, Centrum* c, ostream& outS);
    static void simulate(simulation& s, int n, ostream& outS);
};


#endif //PSE_AUTOSIM_H
