/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the simulationImporter class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 2.0
 */

#include <iostream>
#include <string>
#include <sstream>

#include "Hub.h"
#include "Centrum.h"
#include "simulation.h"
#include "simulationImporter.h"
#include "../XmlParser/tinyxml.h"
#include "algemeen.h"
#include "DesignByContract.h"


bool simulationImporter::checkEmptiness(TiXmlElement* element, ostream& errStr, string* inFile) {
    REQUIRE(!element->GetDocument()->Error(), "Document has a parsing error");
    if (!element->FirstChildElement()) {
        errStr << "empty " << element->Value() << " in file: " + *inFile << endl;
        return true;
    }
    return false;
}

bool simulationImporter::loadFile(TiXmlDocument* doc, string* inFile, ostream& errStr) {
    if (!doc->LoadFile(inFile->c_str())) {
        errStr << "Error reading " + *inFile + ": " << doc->ErrorDesc() << endl;
        return false;
    }
    return !checkEmptiness(doc->FirstChildElement(), errStr, inFile);
}

void simulationImporter::insertCentra(TiXmlDocument* doc, map<string, Centrum *> &centraMap, ostream& errStr) {
    REQUIRE(!doc->Error(), "Document has a parsing error");
    REQUIRE(centraMap.empty(), "Centra already inserted");
    TiXmlElement* root = doc->FirstChildElement();

    unsigned centerCount = 0;

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        if (strcmp( elem->Value(), "VACCINATIECENTRUM" ) == 0) {
            Centrum* centrum = insertCentrum(elem, errStr);
            if (centrum->empty()) {
                delete centrum;
                errStr << "Center containing invalid data" << endl;
                continue;
            }
            if (centraMap.find(centrum->getNaam()) != centraMap.end()) {
                errStr << "Double center definition" << endl;
                delete centrum;
                continue;
            }
            centraMap.insert(pair<string,Centrum*>(centrum->getNaam(), centrum));
            centerCount += 1;
        }
        else if (strcmp( elem->Value(), "HUB" ) != 0){
            errStr << "Invalid element, neither HUB nor VACCINATIECENTRUM" << endl;
        }
    }
    ENSURE(centerCount == centraMap.size(), "insertCentra postcondition failed");
}

Centrum* simulationImporter::insertCentrum(TiXmlElement *elem, ostream& errStr) {
    REQUIRE(!elem->GetDocument()->Error(), "Document has a parsing error");
    vector<string> check;

    Centrum* centrum;
    centrum = new Centrum();
    for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
        if(!centrum->insert(ele,errStr)) {
//            delete centrum;
//            centrum = new Centrum();
            break;
        }
        check.push_back(ele->Value());
    }
    if (check.size() != unsigned (4)) {
        delete centrum;
        centrum = new Centrum();
    }
    ENSURE(centrum->properlyInitialised(), "insertCentrum postcondition failed");
    return centrum;
}

Vaccine* simulationImporter::insertVaccin(TiXmlElement *ele, ostream& errStr) {
    REQUIRE(!ele->GetDocument()->Error(), "Document has a parsing error");
    Vaccine* vaccine;
    vaccine = new Vaccine;
    for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
        if(!vaccine->insert(el, errStr)) {
            delete vaccine;
            vaccine = new Vaccine();
            break;
        }
    }
    ENSURE(vaccine->properlyInitialised(), "insertVaccine postcondition failed");
    return vaccine;
}

Hub* simulationImporter::insertHub(TiXmlElement *elem, map<string, Centrum *> &centraMap, ostream& errStr) {
    REQUIRE(!elem->GetDocument()->Error(), "Document has a parsing error");
    Hub* hub;
    hub = new Hub;
    for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
        if (strcmp( ele->Value(), "VACCIN" ) == 0) {
            Vaccine* vaccine = insertVaccin(ele, errStr);
            if (vaccine->empty()) {
                delete vaccine;
                errStr << "Invalid vaccine in hub" << endl;
                continue;
            }
            hub->addVaccine(vaccine);
        }
        else if (strcmp( ele->Value(), "CENTRA" ) == 0)
            hub->setCentra(insertHubCentra(ele, centraMap, errStr));
        else {
            errStr << "Invalid element, neither VACCIN nor CENTRA" << endl;
        }
    }
    ENSURE(hub->properlyInitialised(), "insetHub postcondition failed");
    return hub;
}

void simulationImporter::insertHubs(TiXmlDocument* doc, map<string, Centrum *> &centraMap,
                                    vector<Hub*>* hubs, ostream& errStr) {
    REQUIRE(!doc->Error(), "Document has a parsing error");
    REQUIRE(hubs->empty(), "Hubs already inserted");
    TiXmlElement* root = doc->FirstChildElement();

    unsigned hubCount = 0;

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        if (strcmp( elem->Value(), "HUB" ) == 0) {
            hubs->push_back(insertHub(elem, centraMap,errStr));
            hubCount += 1;
        }
    }
    ENSURE(hubCount == hubs->size(), "insertHubs postcondition failed");
}

map<string, Centrum*> simulationImporter::insertHubCentra(TiXmlElement *ele, map<string,
                                                          Centrum *> &centraMap, ostream& errStr) {
    REQUIRE(!ele->GetDocument()->Error(), "Document has a parsing error");
    map<string, Centrum*> centra;
    unsigned centerCount = 0;
    for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
        if (!el->FirstChild()) {
            errStr << "Centrum in hub is empty" << endl;
            continue;
        }
        if (strcmp( el->Value(), "centrum" ) != 0) {
            errStr << "Couldn't recoginize element " << el->Value() << " in hub" << endl;
            continue;
        }
        string centrumStr = el->FirstChild()->ToText()->Value();
        if (centra.find(centrumStr) != centra.end()) {
            errStr << "Double definition of center in hub" << endl;
            continue;
        }
        if (centraMap.find(centrumStr) != centraMap.end())
            centra[centrumStr] = centraMap[centrumStr];
        else
            centra[centrumStr] = NULL;
        centerCount += 1;
    }
    ENSURE(centerCount == centra.size(), "insetHubCenta postcondition failed");
    return centra;
}

void simulationImporter::loadSim(simulation* sim, map<string, Centrum*>* centraMap, vector<Hub*>* hubs) {
    REQUIRE(sim->properlyInitialised(), "Simulation wasn't initialised when loading");
    vector<Centrum*> centra;
    map<string, Centrum*>::iterator it;

    for (it = centraMap->begin(); it != centraMap->end(); it++) {
        centra.push_back(it->second);
    }

    sim->setCentra(centra);
    sim->setHubs(*hubs);
    ENSURE(sim->getHubs().size() == hubs->size() && sim->getCentra().size() == centraMap->size(),
           "loadSim postconditions failed");
}

bool simulationImporter::checkConsistent(map<string, Centrum *> &centraMap, vector<Hub *> &hubs, ostream &errStr) {
    bool returnVal = true;
    map<string, bool> linkedCentra;

    if (hubs.size() < unsigned (1)) {
        returnVal = false;
        errStr << "Simulation must contain at least 1 valid hub" << endl;
    }
    if (centraMap.size() < unsigned (1)) {
        returnVal = false;
        errStr << "Simulation must contain at least 1 valid center" << endl;
    }

    for (unsigned i = 0; i < hubs.size(); ++i) {
        Hub* h = hubs[i];
        map<string, Centrum*> cMapH = h->getCentra();
        if (cMapH.size() < unsigned (1)) {
            returnVal = false;
            errStr << "Every hub must at least contain 1 valid center" << endl;
        }

        if (h->getVaccins().size() < unsigned (1)) {
            returnVal = false;
            errStr << "Every hub must al least contain 1 valid vaccine" << endl;
        }

        for (map<string, Centrum*>::iterator it = cMapH.begin(); it != cMapH.end(); it++) {
            if (it->second == NULL) {
                returnVal = false;
                errStr << "Hub contains an invalid center" << endl;
            } else {
                linkedCentra[it->first] = true;
            }
        }
    }

    for (map<string, Centrum*>::iterator it = centraMap.begin(); it != centraMap.end(); it++) {
        if (linkedCentra.find(it->first) == linkedCentra.end()) {
            returnVal = false;
            errStr << "Centrum is not linked to hub" << endl;
        }
    }

    return returnVal;
}

int simulationImporter::importFile(string inFile, simulation &sim, ostream& errStr) {
    REQUIRE(sim.properlyInitialised(), "Simulation wasn't initialised when importing file");
    sim.clear();
    TiXmlDocument doc;
    map<string, Centrum*> centraMap;
    vector<Hub*> hubs;

    if( !loadFile(&doc, &inFile, errStr))
        return 1;

    insertCentra(&doc, centraMap, errStr);
    insertHubs(&doc, centraMap, &hubs, errStr);

    if (checkConsistent(centraMap, hubs, errStr))
        loadSim(&sim, &centraMap, &hubs);
    else
        return 1;
    doc.Clear();
    ENSURE(!sim.getHubs().empty() && !sim.getCentra().empty(),"importFile postconditions failed");
    return 0;
}