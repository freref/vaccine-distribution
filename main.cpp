#include <iostream>
#include "XmlParser/tinyxml.h"
#include <vector>
#include "Simulation/Centrum.h"
#include "Simulation/Hub.h"
#include "Simulation/simulation.h"
#include "Simulation/simulationImporter.h"
#include "Simulation/simulationExporter.h"
#include <string>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    simulation s;

    simulationImporter::importFile("data1.xml", s);

//    ofstream myFile("output.txt");
    simulationExporter exporter;
    exporter.exportSim(cout, s);

    return 0;
}