//
// Created by sande on 9/03/2021.
//

#include <map>
#include <vector>

#include "simulationExporter.h"
#include "simulation.h"
#include "Hub.h"
#include "Centrum.h"

void simulationExporter::exportSim(ostream &ostream, const simulation &sim) {
    Hub* hub = sim.getHub();
    ostream << "Hub (" << hub->getLevering() << ")\n";
    map<string, Centrum*> hCentra = hub->getCentra();
    for (map<string, Centrum*>::iterator it = hCentra.begin(); it != hCentra.end(); it++) {
        ostream << "\t-> " << it->second->getNaam() << " (" << it->second->getVaccins() << ")\n";
    }
    ostream << endl;
    vector<Centrum*> centra = sim.getCentra();
    for (int i = 0; i < centra.size(); i++) {
        Centrum* c = centra[i];
        ostream << c->getNaam() << ": " << c->getGevaccineerd() << " gevaccineerd, nog ";
        int teGaan = c->getInwoners() - c->getGevaccineerd();
        ostream << teGaan << " inwoners niet gevaccineerd\n";
    }
}
