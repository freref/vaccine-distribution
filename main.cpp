#include <iostream>
#include "XmlParser/tinyxml.h"
#include <vector>
#include "Simulation/Centrum.h"
#include "Simulation/Hub.h"
#include "Simulation/simulation.h"
#include "Simulation/simulationImporter.h"
#include "Simulation/autoSim.h"
#include <string>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    simulation s;

    if (simulationImporter::importFile("data2.xml", s, cerr) == 0) {
        s.exportSim(cout);

        cout << endl;

        autoSim::simulate(s, 1000, cout);
        ofstream MyFile("../graphic_impression.txt");
        s.graphicImpression(MyFile);
        MyFile.close();

        cout << endl;

        s.exportSim(cout);
    }

    return 0;
}