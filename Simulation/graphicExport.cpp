//
// Created by sande on 13/05/2021.
//

#include "graphicExport.h"
#include <iomanip>
#include <sstream>
#include <cmath>

inline double calculateCenterOffset(int cNum, int cOffset) {
    return (pow(-1, cNum) * cOffset/2.0) + (pow(-1, cNum) * floor(cNum/2.0) * cOffset);
}

vector<double> graphicExport::calculateGradient(int maxVal, int curVal) {
    // Calculate capacity load
    double percent = double (curVal) / maxVal;
    double green = (percent * 2);
    double red = 1;
    if (green > 1)
        // Red caps at 1 when center halfway stocked
        green = 1;
    if (green == 1)
        // Green starts to decrease once over halfway mark
        red -= (percent - 0.50) * 2.0;

    vector<double> color;
    color.push_back(red);
    color.push_back(green);
    color.push_back(0);

    return color;
}

void
graphicExport::createIni(const Hub *hub, unsigned int hubNum, int stockDivide, map<Centrum *, int> &transports, int day,
                         const string &path) {
    ostringstream conv;
    conv << setw(2) << setfill('0') << hubNum;
    string fPath = path + "/hub" + conv.str();
    conv.str("");
    conv << setw(4) << setfill('0')<< day;
    fPath += "_dag" + conv.str() + ".ini";

    ofstream oFile(fPath.c_str());

    int cOffset = 3;
    int tOffset = 2;

    int maxTransport = 0;

    int figAmount = 0;
    int cAmount = 0;

    // Hub toevoegen aan ini
    iniAddHub(figAmount, oFile);
    figAmount += 1;
    figAmount = iniAddHubStock(hub, figAmount, stockDivide, 1, oFile);

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

    iniGeneral(figAmount, maxTransport, oFile);

    oFile.close();
}

void graphicExport::iniAdd3dVectorSegment(string type, double x, double y, double z, ofstream& oFile) {
    ostringstream conv;

    oFile << type << " = (";
    // Rood
    conv.str("");
    conv << x;
    oFile << conv.str() << ", ";
    // Groen
    conv.str("");
    conv << y;
    oFile << conv.str() << ", ";
    // Blauw
    conv.str("");
    conv << z;
    oFile << conv.str() << ")" << endl;
}

void graphicExport::iniAddHub(int figNum, ofstream &oFile) {
    ostringstream conv;

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
             "center = (0, -4, 0)\n"
             "reflectionCoefficient = 10\n\n";
}

int graphicExport::iniAddHubStock(const Hub *h, int figNum, int stockDivide, int sOffset, ofstream &oFile) {
    ostringstream conv;

    int stockAmount = ceil(float (h->getTotaleVoorraad()) / stockDivide);

    for (int i = 0; i < stockAmount; ++i) {
        conv.str("");
        conv << figNum;

        oFile << "[Figure" << conv.str() << "]\n";
        oFile << "type = \"Cube\"\n"
                 "scale = 0.25\n"
                 "rotateX = 0\n"
                 "rotateY = 0\n"
                 "rotateZ = 0\n"
                 "ambientReflection = (0.2, 0.2, 0.2)\n"
                 "diffuseReflection = (0.1, 0.1, 0.7)\n"
                 "specularReflection = (0.5, 0.5, 0.5)\n"
                 "reflectionCoefficient = 10\n";
        iniAdd3dVectorSegment("center", calculateCenterOffset(i % 10, sOffset),
                              -4, 2 + (floor(float(i) / 10) * sOffset), oFile);
        oFile << endl;

        figNum += 1;
    }

    return figNum;
}

void graphicExport::iniAddCenter(Centrum *c, int cNum, int figNum, int cOffset, ofstream &oFile) {
    double xOffset = calculateCenterOffset(cNum, cOffset);

    // Get color gradient for center based on percentage vaccinated
    vector<double> color = calculateGradient(c->getInwoners(), c->getGevaccineerd());
    double red = color[0];
    double green = color[1];
    double blue = color[2];

    ostringstream convert;
    convert << figNum; // Get figure number in file
    // Add a figure to represent the center
    oFile << "[Figure" << convert.str() << "]\n";
    oFile << "type = \"Cube\"\n"
             "scale = 1\n"
             "rotateX = 0\n"
             "rotateY = 0\n"
             "rotateZ = 0\n";
    iniAdd3dVectorSegment("center", xOffset, 0, 0, oFile);
    // Add color of center
    iniAdd3dVectorSegment("ambientReflection", red / 4, green / 4, blue / 4, oFile);
    iniAdd3dVectorSegment("diffuseReflection", red, green, blue, oFile);
    oFile << "specularReflection = (0.5, 0.5, 0.5)" << endl;
    oFile << "reflectionCoefficient = 10" << endl;
    oFile << endl;

    // Get color gradient depending on remaining storage capacity
    color = calculateGradient(c->getCapaciteit() * 2, c->getVaccins());
    red = color[0];
    green = color[1];
    blue = color[2];

    convert.str("");
    convert << figNum + 1;
    // Add roof to center to show storage capacity
    oFile << "[Figure" << convert.str() << "]\n";
    oFile << "type = \"Octahedron\"\n"
             "scale = 1.40\n"
             "rotateX = 0\n"
             "rotateY = 0\n"
             "rotateZ = 45\n";
    // Calculate offset
    iniAdd3dVectorSegment("center", xOffset, 0, 1, oFile);
    // Add color of center
    iniAdd3dVectorSegment("ambientReflection", red / 4, green / 4, blue / 4, oFile);
    iniAdd3dVectorSegment("diffuseReflection", red, green, blue, oFile);
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
        iniAdd3dVectorSegment("center", calculateCenterOffset(centerNum, cOffset),
                              1.5 + (i * tOffset), 0, oFile);
        // Color parameters
        oFile << "ambientReflection = (0.5, 0.5, 0.5)" << endl;
        oFile << "diffuseReflection = (0.1, 0.1, 0.1)" << endl;
        oFile << "specularReflection = (0.2, 0.2, 0.2)" << endl;
        oFile << "reflectionCoefficient = 10" << endl;
        oFile << endl;
    }
}

void graphicExport::iniGeneral(int figAmount, int maxTrans, ofstream &oFile) {
    int yOffset = 10 + maxTrans * 10;
    double xOffset = 0;

    ostringstream conv;

    oFile << "[General]\n"
             "size = 2048\n"
             "backgroundcolor = (0, 0, 0)\n"
             "type = \"LightedZBuffering\"\n";
    iniAdd3dVectorSegment("eye", xOffset, yOffset, 10, oFile);
    // Add figures
    conv.str("");
    conv << figAmount;
    oFile << "nrFigures = " << conv.str() << endl;
    oFile << "nrLights = 1\n" << endl;
    // Add a light
    oFile << "[Light0]\n"
             "infinity = FALSE\n"
             "location = (0, ";
    conv.str("");
    conv << yOffset;
    oFile << yOffset;
    oFile << ", 10)\n"
             "ambientLight = (0.9, 0.9, 0.9)\n"
             "diffuseLight = (1, 1, 1)\n"
             "specularLight = (0.2, 0.2, 0.2)" << endl;
}
