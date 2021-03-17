/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class to export the simulation class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */


#ifndef PROJECTPSE_SIMULATIONEXPORTER_H
#define PROJECTPSE_SIMULATIONEXPORTER_H

#include <iostream>

using namespace std;

class simulation;

class simulationExporter {
public:
    /**
     * \n REQUIRE(sim.properlyInitialised(), "simulation wasn't initialised when calling exporter");
     * \n export the stream in ostream output
     * @param ostream
     * @param sim
     */
    static void exportSim(ostream& ostream, const simulation& sim);
};


#endif //PROJECTPSE_SIMULATIONEXPORTER_H
