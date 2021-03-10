//
// Created by sande on 4/03/2021.
//

#ifndef PROJECTPSE_SIMULATIONIMPORTER_H
#define PROJECTPSE_SIMULATIONIMPORTER_H

#include <string>

using namespace std;

class simulation;

class simulationImporter {
public:
    static int importFile(const string& inFile, simulation& sim);
};


#endif //PROJECTPSE_SIMULATIONIMPORTER_H
