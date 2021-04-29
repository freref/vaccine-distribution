/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class to import a simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 2.0
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
    static bool checkEmptiness(TiXmlElement *element, ostream &errStr, string *inFile);

    static bool loadFile(TiXmlDocument *doc, string *inFile, ostream &errStr);

    static bool insertCentra(TiXmlDocument* doc, map<string, Centrum *>* centraMap, ostream& errStr);

    static Centrum* insertCentrum(TiXmlElement *elem, ostream& errStr);

    static Vaccine* insertVaccin(TiXmlElement *ele, ostream& errStr);

    static Hub* insertHub(TiXmlElement *elem, map<string, Centrum *>* centraMap, ostream& errStr);

    static bool insertHubs(TiXmlDocument* doc, map<string, Centrum *>* centraMap, vector<Hub*>* hubs, ostream& errStr);

    static map<string, Centrum*> insertHubCentra(TiXmlElement *ele, map<string, Centrum *>* centraMap, ostream& errStr);

    static void loadSim(simulation* sim, map<string, Centrum*>* centraMap, vector<Hub*>* hubs);

    /**
     * imports the file into sim object
     * @param inFile:   Input filename
     * @param sim:      Simulation to import to
     * @param errStr:   Error output stream
     * @return int  Error code (1: Error reading file, 2: Bad file format)
     */
    static int importFile(string inFile, simulation &sim, ostream &errStr);

    /**
     * checks if centrum has correct input
     * @param elements: Map containing different centrum elements (elemName: elemValue, ...)
     * @param errStr:   Error output stream
     * @return bool Correct centrum
     */
    static bool isCoorectCentrum(map<string, string> elements, ostream &errStr);

    /**
     * checks if element names inside hubs and centrum are correct
     * @param name: Element name to check
     * @return bool Correct element name
     */
    static bool checkName(string name);

    /**
     * checks if element names are correct (HUB and VACCINATIECENTRUM)
     * @param name: Name of element to check
     * @return  bool Correct element name
     */
    static bool checkElementName(string name);
};


#endif //PROJECTPSE_SIMULATIONIMPORTER_H
