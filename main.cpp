#include <iostream>
#include "XmlParser/tinyxml.h"
#include <vector>
#include "Simulation/Centrum.h"
#include "Simulation/Hub.h"
#include "Simulation/simulation.h"
#include "Simulation/simulationImporter.h"
#include "Simulation/simulationExporter.h"
#include "Simulation/autoSim.h"
#include <string>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    simulation s;

    if (simulationImporter::importFile("data1.xml", s, cerr) == 0) {
        simulationExporter::exportSim(cout, s);

        cout << endl;

        autoSim::simulate(s, 100, cout);
//    ofstream myFile("output.txt");

        cout << endl;

        simulationExporter::exportSim(cout, s);
    }

//    if (simulationImporter::importFile("data1.xml", s, cout) == 0) {
//        simulationExporter::exportSim(cout, s);
//    }

    return 0;
}