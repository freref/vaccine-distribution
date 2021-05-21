//
// Created by sande on 13/05/2021.
//

#include "graphicExport.h"
#include <sstream>
#include <cmath>

inline double calculateCenterOffset(int cNum, int cOffset) {
    return (pow(-1, cNum) * cOffset/2.0) + (pow(-1, cNum) * floor(cNum/2.0) * cOffset);
}

vector<double> graphicExport::calculateGradient(int maxVal, int curVal) {
    // Calculate capacity load
    double percent = double (curVal) / maxVal;
    double redRef = (percent * 2);
    double greenRef = 1;
    if (redRef > 1)
        // Red caps at 1 when center halfway stocked
        redRef = 1;
    if (redRef == 1)
        // Green starts to decrease once over halfway mark
        greenRef -= (percent - 0.50) * 2.0;

    vector<double> color;
    color.push_back(redRef);
    color.push_back( greenRef);
    color.push_back(0);

    return color;
}

void graphicExport::createIni(const Hub *hub, unsigned int hubNum, map<Centrum *, int> &transports, int day,
                              const string &path) {
    ostringstream conv;
    conv << hubNum;
    string fPath = path + "/hub" + conv.str();
    conv.str("");
    conv << day;
    fPath += "_dag" + conv.str() + ".ini";

    ofstream oFile(fPath.c_str());

    int cOffset = 3;
    int tOffset = 2;

    int maxTransport;

    int figAmount = 0;
    int cAmount = 0;

    // Hub toevoegen aan ini
    iniAddHub(hub, figAmount, oFile);
    figAmount += 1;

    // Centra en transporten toevoegen aan ini
    map<string, Centrum*> centra = hub->getCentra();
    for (map<string, Centrum*>::iterator it = centra.begin(); it != centra.end(); it++) {
        // Centrum toevoegen
        iniAddCenter(it->second, cAmount, figAmount, cOffset, oFile);
        figAmount += 2;
        int transportAmount = transports[it->second];
        // Correct aantal transporten toevoegen
        iniAddTransports(transportAmount, cAmount, figAmount, cOffset, tOffset, oFile);

        if (transportAmount > maxTransport)
            maxTransport = transportAmount;

        cAmount += 1;
        figAmount += transportAmount;
    }

    iniGeneral(figAmount, cAmount, maxTransport, cOffset, oFile);

    oFile.close();
}

void graphicExport::iniAddHub(const Hub *h, int figNum, ofstream &oFile) {
    ostringstream conv;

    h->getVaccins();

    conv << figNum;
    oFile << "[Figure" << conv.str() << "]\n";
    oFile << "type = \"Cone\"\n"
             "scale = 1\n"
             "rotateX = 0\n"
             "rotateY = 0\n"
             "rotateZ = 0\n"
             "n = 10\n"
             "height = 2\n"
             "ambientReflection = (0.2, 0.2, 0.2)\n"
             "diffuseReflection = (0.1, 0.1, 0.1)\n"
             "specularReflection = (0.5, 0.5, 0.5)\n"
             "center = (0 , -4, 0)\n"
             "reflectionCoefficient = 10\n\n";
}

void graphicExport::iniAddCenter(Centrum *c, int cNum, int figNum, int cOffset, ofstream &oFile) {
    vector<double> color = calculateGradient(c->getInwoners(), c->getGevaccineerd()); // Get color of center

    double xOffset = calculateCenterOffset(cNum, cOffset);

    ostringstream convert;
    convert << figNum; // Get figure number in file

    oFile << "[Figure" << convert.str() << "]\n";
    oFile << "type = \"Cube\"\n"
             "scale = 1\n"
             "rotateX = 0\n"
             "rotateY = 0\n"
             "rotateZ = 0\n";
    oFile << "center = (";
    // Calculate offset
    convert.str("");
    convert << xOffset;
    oFile << convert.str() << ", 0, 0)" << endl;
    // Add color of center
    oFile << "ambientReflection = (";
    // Rood
    convert.str("");
    convert << color[0] / 4.0;
    oFile << convert.str() << ", ";
    // Groen
    convert.str("");
    convert << color[1] / 4.0;
    oFile << convert.str() << ", ";
    // Blauw
    convert.str("");
    convert << color[2] / 4.0;
    oFile << convert.str() << ")" << endl;
    // Other light parameters
    oFile << "diffuseReflection = (";
    // Rood
    convert.str("");
    convert << color[0];
    oFile << convert.str() << ", ";
    // Groen
    convert.str("");
    convert << color[1];
    oFile << convert.str() << ", ";
    // Blauw
    convert.str("");
    convert << color[2];
    oFile << convert.str() << ")" << endl;
    oFile << "specularReflection = (0.5, 0.5, 0.5)" << endl;
    oFile << "reflectionCoefficient = 10" << endl;
    oFile << endl;

    color = calculateGradient(c->getCapaciteit() * 2, c->getVaccins());

    convert.str("");
    convert << figNum + 1;
    oFile << "[Figure" << convert.str() << "]\n";
    oFile << "type = \"Sphere\"\n"
             "n = 3\n"
             "scale = 1\n"
             "rotateX = 0\n"
             "rotateY = 0\n"
             "rotateZ = 0\n";
    oFile << "center = (";
    // Calculate offset
    convert.str("");
    convert << xOffset;
    oFile << convert.str() << ", 0, 1)" << endl;
    // Add color of center
    oFile << "ambientReflection = (";
    // Rood
    convert.str("");
    convert << color[0] / 4.0;
    oFile << convert.str() << ", ";
    // Groen
    convert.str("");
    convert << color[1] / 4.0;
    oFile << convert.str() << ", ";
    // Blauw
    convert.str("");
    convert << color[2] / 4.0;
    oFile << convert.str() << ")" << endl;
    // Other light parameters
    oFile << "diffuseReflection = (";
    // Rood
    convert.str("");
    convert << color[0];
    oFile << convert.str() << ", ";
    // Groen
    convert.str("");
    convert << color[1];
    oFile << convert.str() << ", ";
    // Blauw
    convert.str("");
    convert << color[2];
    oFile << convert.str() << ")" << endl;
    oFile << "specularReflection = (0.5, 0.5, 0.5)" << endl;
    oFile << "reflectionCoefficient = 10" << endl;
    oFile << endl;
}

void graphicExport::iniAddTransports(int amount, int centerNum, int figNum, int cOffset, int tOffset, ofstream &oFile) {
    for (int i = 0; i < amount ; ++i) {
        ostringstream convert;
        convert << figNum + i; // Get figure number in file

        oFile << "[Figure" << convert.str() << "]" << endl;
        oFile << "type = \"Cube\"\n"
                 "scale = 0.25\n"
                 "rotateX = 0\n"
                 "rotateY = 0\n"
                 "rotateZ = 0\n";
        // Calculate center
        oFile << "center = (";
        // X offset
        convert.str("");
        convert << calculateCenterOffset(centerNum, cOffset);
        oFile << convert.str() << ", ";
        // Y offset
        convert.str("");
        convert << 1.5 + (i * tOffset);
        oFile << convert.str() << ", 0)" << endl;
        // Color parameters
        oFile << "ambientReflection = (0.5, 0.5, 0.5)" << endl;
        oFile << "diffuseReflection = (0.1, 0.1, 0.1)" << endl;
        oFile << "specularReflection = (0.2, 0.2, 0.2)" << endl;
        oFile << "reflectionCoefficient = 10" << endl;
        oFile << endl;
    }
}

void graphicExport::iniGeneral(int figAmount, int cAmount, int maxTrans, int cOffset, ofstream &oFile) {
//    double xOffset = ((cAmount - 1) * cOffset)/2.0;
    int yOffset = maxTrans * 10;
    double xOffset = 0;

    ostringstream conv;

    oFile << "[General]\n"
             "size = 2048\n"
             "backgroundcolor = (0, 0, 0)\n"
             "type = \"LightedZBuffering\"\n"
             "eye = (";
    // Eye gets centered between al centers in simulation
    conv << xOffset;
    oFile << conv.str() << ", ";
    // Make sure eye is far enough for the transports
    conv.str("");
    conv << yOffset;
    oFile << conv.str() << ", 10)\n";
    // Add figures
    conv.str("");
    conv << figAmount;
    oFile << "nrFigures = " << conv.str() << endl;
    oFile << "nrLights = 1\n" << endl;
    // Add a light
    oFile << "[Light0]\n"
             "infinity = FALSE\n"
             "location = (-1, ";
    conv.str("");
    conv << yOffset;
    oFile << yOffset;
    oFile << ", 10)\n"
             "ambientLight = (0.9, 0.9, 0.9)\n"
             "diffuseLight = (1, 1, 1)\n"
             "specularLight = (0.2, 0.2, 0.2)" << endl;
}
