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
    /**
     \n Check whether xml element is empty
     \n REQUIRE(!element->GetDocument()->Error(), "Document has a parsing error")
     * @param element:  Element to check
     * @param errStr:   Error output
     * @param inFile:   Input file
     * @return      true if empty
     */
    static bool checkEmptiness(TiXmlElement *element, ostream &errStr, string *inFile);

    /**
     \n Parses a xml file
     * @param doc:      TiXmlDocument parse file to
     * @param inFile:   Name of file to parse
     * @param errStr:   Error output
     * @return      True if succes
     */
    static bool loadFile(TiXmlDocument *doc, string *inFile, ostream &errStr);

    /**
     \n Adds centra from the xml file
     \n REQUIRE(!doc->Error(), "Document has a parsing error")
     \n REQUIRE(centraMap.empty(), "Centra already inserted")
     \n ENSURE(centerCount == centraMap.size(), "insertCentra postcondition failed")
     * @param doc:          Parsed xml file
     * @param centraMap:    Map to store all created centra linked to name
     * @param errStr:       Error output
     */
    static void insertCentra(TiXmlDocument* doc, map<string, Centrum *> &centraMap, ostream& errStr);

    /**
     \n Create a center from xml data
     \n REQUIRE(!elem->GetDocument()->Error(), "Document has a parsing error")
     \n ENSURE(centrum->properlyInitialised(), "insertCentrum postcondition failed")
     * @param elem:     Parsed xml element containing center data
     * @param errStr:   Error output
     * @return      Created center
     */
    static Centrum* insertCentrum(TiXmlElement *elem, ostream& errStr);

    /**
     \n Create a vaccine from xml data
     \n REQUIRE(!ele->GetDocument()->Error(), "Document has a parsing error")
     \n ENSURE(vaccine->properlyInitialised(), "insertVaccine postcondition failed")
     * @param ele:      Parsed xml element containing vaccine data
     * @param errStr:   Error output
     * @return      Created vaccine
     */
    static Vaccine* insertVaccin(TiXmlElement *ele, ostream& errStr);

    /**
     \n Create a hub from xml data
     \n REQUIRE(!elem->GetDocument()->Error(), "Document has a parsing error")
     \n ENSURE(hub->properlyInitialised(), "insetHub postcondition failed")
     * @param elem:         Parsed xml element containing hub data
     * @param centraMap:    Map containing all created centra linked to name
     * @param errStr:       Error output
     * @return          Created hub
     */
    static Hub* insertHub(TiXmlElement *elem, map<string, Centrum *> &centraMap, ostream& errStr);

    /**
     \n Adds hubs from the xml file
     \n REQUIRE(!doc->Error(), "Document has a parsing error")
     \n REQUIRE(hubs->empty(), "Hubs already inserted")
     \n ENSURE(hubCount == hubs->size(), "insertHubs postcondition failed")
     * @param doc:          Parsed xml file
     * @param centraMap:    Map containing all created centra linked to name
     * @param hubs:         Vector to store all created hubs
     * @param errStr:       Error output
     */
    static void insertHubs(TiXmlDocument* doc, map<string, Centrum *> &centraMap, vector<Hub*>* hubs, ostream& errStr);

    /**
     \n Link centra to a hub from parsed xml element
     \n REQUIRE(!ele->GetDocument()->Error(), "Document has a parsing error")
     \n ENSURE(centerCount == centra.size(), "insetHubCenta postcondition failed")
     * @param ele:          Parsed xml element containing centra linked to hub
     * @param centraMap:    Map containing created centra
     * @param errStr:       Error output
     * @return          Map containing centra linked to hub
     */
    static map<string, Centrum*> insertHubCentra(TiXmlElement *ele, map<string, Centrum *> &centraMap, ostream& errStr);

    /**
     \n Load created data into simulation
     \n REQUIRE(sim->properlyInitialised(), "Simulation wasn't initialised when loading")
     \n ENSURE(sim->getHubs().size() == hubs->size() && sim->getCentra().size() == centraMap->size(),
              "loadSim postconditions failed")
     * @param sim:          Simulation to add data to
     * @param centraMap:    Created centra for simulation
     * @param hubs:         Created hubs for simulation
     */
    static void loadSim(simulation* sim, map<string, Centrum*>* centraMap, vector<Hub*>* hubs);

    /**
     \n Check whether created data will make a consistent simulation
     * @param centraMap:    Created centra
     * @param hubs:         Created hubs
     * @param errStr:       Error output
     * @return          Bool whether consistent
     */
    static bool checkConsistent(map<string, Centrum *> &centraMap, vector<Hub *> &hubs, ostream &errStr);

    /**
     \n Imports a file into sim object
     \n REQUIRE(sim.properlyInitialised(), "Simulation wasn't initialised when importing file")
     \n ENSURE(!sim.getHubs().empty() && !sim.getCentra().empty(),"importFile postconditions failed");
     * @param inFile:   Input filename
     * @param sim:      Simulation to import to
     * @param errStr:   Error output stream
     * @return int  Error code (1: Error reading file, Bad file format)
     */
    static int importFile(string inFile, simulation &sim, ostream &errStr);
};


#endif //PROJECTPSE_SIMULATIONIMPORTER_H
