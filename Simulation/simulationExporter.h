//
// Created by sande on 9/03/2021.
//

#ifndef PROJECTPSE_SIMULATIONEXPORTER_H
#define PROJECTPSE_SIMULATIONEXPORTER_H

#include <iostream>

using namespace std;

class simulation;

class simulationExporter {
public:
    void exportSim(ostream& ostream, const simulation& sim);
};


#endif //PROJECTPSE_SIMULATIONEXPORTER_H
