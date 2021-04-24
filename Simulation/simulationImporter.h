/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class to import a simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 1.0
 */

#ifndef PROJECTPSE_SIMULATIONIMPORTER_H
#define PROJECTPSE_SIMULATIONIMPORTER_H

#include <string>
#include <iostream>
#include <map>
#include "../XmlParser/tinyxml.h"

using namespace std;

class simulation;

class simulationImporter {
public:
    void vaccinInsert(TiXmlElement* el, Vaccine* v);
    /**
     * imports the file into sim object
     * @param inFile
     * @param sim
     * @param errStr
     * @return int
     */
    static int importFile(string inFile, simulation& sim, ostream& errStr);
    /**
     * checks if centrum has correct input
     * @param elements
     * @param errStr
     * @return
     */
    static bool isCoorectCentrum(map<string, string> elements, ostream& errStr);
    /**
     * checks if element names inside hubs and centrum are correct
     * @param name
     * @return
     */
    static bool checkName(string name);
    /**
     * checks if element names are correct (HUB and VACCINATIECENTRUM)
     * @param name
     * @return
     */
    static bool checkElementName(string name);
    };


#endif //PROJECTPSE_SIMULATIONIMPORTER_H
