/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the simulationExporter class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#include <map>
#include <vector>

#include "simulationExporter.h"
#include "simulation.h"
#include "Hub.h"
#include "Centrum.h"
#include "DesignByContract.h"

void simulationExporter::exportSim(ostream &ostream, const simulation &sim) {
    REQUIRE(sim.properlyInitialised(), "simulation wasn't initialised when calling exporter");
    Hub* hub = sim.getHub();
    ostream << "Hub (" << hub->accessorVoorraad() << ")\n";
    map<string, Centrum*> hCentra = hub->getCentra();
    for (map<string, Centrum*>::iterator it = hCentra.begin(); it != hCentra.end(); it++) {
        ostream << "\t-> " << it->second->getNaam() << " (" << it->second->getVaccins() << " vaccins" << ")\n";
    }
    ostream << endl;
    vector<Centrum*> centra = sim.getCentra();
    for (long unsigned int i = 0; i < centra.size(); i++) {
        Centrum* c = centra[i];
        ostream << c->getNaam() << ": " << c->getGevaccineerd() << " gevaccineerd, nog ";
        int teGaan = c->getInwoners() - c->getGevaccineerd();
        ostream << teGaan << " inwoners niet gevaccineerd\n";
    }
}
