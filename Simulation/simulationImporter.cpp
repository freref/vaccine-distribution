
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


bool simulationImporter::checkEmptiness(TiXmlElement* element, ostream& errStr, string* inFile){
    if (!element->FirstChildElement()) {
        errStr << "empty " << element->Value() << " in file: " + *inFile << endl;
        return true;
    }
    return false;
}

bool simulationImporter::loadFile(TiXmlDocument* doc, string* inFile, ostream& errStr){
    if (!doc->LoadFile(inFile->c_str())) {
        errStr << "Error reading " + *inFile + ": " << doc->ErrorDesc() << endl;
        return false;
    }
    return !checkEmptiness(doc->FirstChildElement(), errStr, inFile);
}

Vaccine* simulationImporter::insertVaccin(TiXmlElement *ele, ostream& errStr){
    Vaccine* vaccine;
    vaccine = new Vaccine;
    for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
        if(!vaccine->insert(el, errStr)){
            delete vaccine;
            return new Vaccine;
        }
    }
    return vaccine;
}

map<string, Centrum*> simulationImporter::insertHubCentra(TiXmlElement *ele, map<string, Centrum *>* centraMap, ostream& errStr){
    map<string, Centrum*> centra;
    for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
        string centrum = el->FirstChild()->ToText()->Value();
        if (centrum == "")
            errStr << "Centrum in hub is leeg";

        centra[centrum] = centraMap->at(centrum);
    }
    return centra;
}

Hub* simulationImporter::insertHub(TiXmlElement *elem, map<string, Centrum *>* centraMap, ostream& errStr){
    Hub* hub;
    hub = new Hub;
    for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
        if (strcmp( ele->Value(), "VACCIN" ) == 0){
            Vaccine* vaccine = insertVaccin(ele, errStr);
            if (vaccine->empty()){
                delete hub;
                return new Hub;
            }
            hub->addVaccine(vaccine);
        }
        else if (strcmp( ele->Value(), "CENTRA" ) == 0)
            hub->setCentra(insertHubCentra(ele, centraMap, errStr));
        else{
            errStr << "Invalid element neither VACCIN nor CENTRA" << endl;
        }
    }
    return hub;
}

bool simulationImporter::insertHubs(TiXmlDocument* doc, map<string, Centrum *>* centraMap, vector<Hub*>* hubs, ostream& errStr){
    TiXmlElement* root = doc->FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        if (strcmp( elem->Value(), "HUB" ) == 0){
            hubs->push_back(insertHub(elem, centraMap,errStr));
        }
    }
    return true;
}

Centrum* simulationImporter::insertCentrum(TiXmlElement *elem, ostream& errStr){
    Centrum* centrum;
    centrum = new Centrum;
    for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
        if(!centrum->insert(ele,errStr)){
            delete centrum;
            return new Centrum;
        }
    }
    return centrum;
}

bool simulationImporter::insertCentra(TiXmlDocument* doc, map<string, Centrum *>* centraMap, ostream& errStr){
    TiXmlElement* root = doc->FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        if (strcmp( elem->Value(), "VACCINATIECENTRUM" ) == 0){
            Centrum* centrum = insertCentrum(elem, errStr);
            if (centrum->empty()){
                delete centrum;
                return false;
            }
            centraMap->insert(pair<string,Centrum*>(centrum->getNaam(), centrum));
        }
        else if (strcmp( elem->Value(), "HUB" ) != 0){
            errStr << "Invalid element, neither HUB nor VACCINATIECENTRUM";
            return false;
        }
    }
    return true;
}

void simulationImporter::loadSim(simulation* sim, map<string, Centrum*>* centraMap, vector<Hub*>* hubs){
    vector<Centrum*> centra;
    map<string, Centrum*>::iterator it;

    for (it = centraMap->begin(); it != centraMap->end(); it++) {
        centra.push_back(it->second);
    }

    sim->setCentra(centra);
    sim->setHubs(*hubs);
}

int simulationImporter::importFile(string inFile, simulation &sim, ostream& errStr){
    sim.clear();
    TiXmlDocument doc;
    map<string, Centrum*> centraMap;
    vector<Hub*> hubs;

    if( !loadFile(&doc, &inFile, errStr) ||
        !insertCentra(&doc, &centraMap, errStr) ||
        !insertHubs(&doc, &centraMap, &hubs, errStr))
        return 1;

    loadSim(&sim, &centraMap, &hubs);
    doc.Clear();

    return 0;
}