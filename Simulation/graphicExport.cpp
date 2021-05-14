//
// Created by sande on 13/05/2021.
//

#include "graphicExport.h"
#include <sstream>
#include <cmath>

vector<double> graphicExport::getCenterColor(Centrum* c) {
    int maxCap = c->getCapaciteit() * 2;
    int stock = c->getVaccins();
    // Calculate capacity load
    double percent = double (stock) / maxCap;
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

void graphicExport::createIni(map<Centrum *, int> &transports, int day, string& path) {
    ostringstream convert;
    convert << day;
    // File name
    string filePath = path + "/dag" + convert.str() + ".ini";

    ofstream oFile;
    oFile.open(filePath.c_str());

    // Values for offset between centers and transports
    int cOffset = 3;
    int tOffset = 1;

    int figAmount = 0;
    int cAmount = 0;

    int maxTransport;
    // Add the centers and transports
    for (map<Centrum*, int>::iterator it = transports.begin(); it != transports.end(); it++) {
        iniAddCenter(it->first, cAmount, figAmount, cOffset, oFile);
        iniAddTransports(it->second, cAmount, figAmount, cOffset, tOffset, oFile);

        if (it->second > maxTransport)
            maxTransport = it->second;

        cAmount += 1;
        figAmount += 1 + it->second;
    }
    // Add general section
    iniGeneral(figAmount, cAmount, maxTransport, cOffset, oFile);
    oFile.close();
}

inline double calculateCenterOffset(int cNum, int cOffset) {
    return (pow(-1, cNum) * cOffset/2.0) + (pow(-1, cNum) * floor(cNum/2.0) * cOffset);
}

void graphicExport::iniAddCenter(Centrum *c, int cNum, int figNum, int cOffset, ofstream &oFile) {
    vector<double> color = getCenterColor(c); // Get color of center

    double xOffset = calculateCenterOffset(cNum, cOffset);

    ostringstream convert;
    convert << figNum; // Get figure number in file

    oFile << "[Figure" << convert.str() << "]" << endl;
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

    // Other light parameters
    oFile << "diffuseReflection = (0.1, 0.1, 0.1)" << endl;
    oFile << "specularReflection = (0.5, 0.5, 0.5)" << endl;
    oFile << endl;
}

void graphicExport::iniAddTransports(int amount, int centerNum, int figNum, int cOffset, int tOffset, ofstream &oFile) {
    for (int i = 1; i <= amount ; ++i) {
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
        convert << 1 + (i * tOffset);
        oFile << convert.str() << ", 0)" << endl;
        // Color parameters
        oFile << "ambientReflection = (0.5, 0.5, 0.5)" << endl;
        oFile << "diffuseReflection = (0.1, 0.1, 0.1)" << endl;
        oFile << "specularReflection = (0.2, 0.2, 0.2)" << endl;
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
