/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class to import a simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 1.0
 */

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
