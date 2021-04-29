
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

/*
bool simulationImporter::isCoorectCentrum(map<string, string> elements, ostream& errStr) {
    if (elements["naam"] != "" && elements["adres"] != "" && algemeen::stoi(elements["inwoners"]) > 0 &&
        algemeen::stoi(elements["capaciteit"]) > 0)
        return true;

    errStr << "Het bestand bevat foute informatie voor vaccinatiecentrum: " << elements["naam"] << endl;
    return false;
}

bool isCorrectHub(map<string, string> elements, ostream& errStr) {
    if (algemeen::stoi(elements["levering"]) > 0 && algemeen::stoi(elements["interval"]) > 0
        && algemeen::stoi(elements["transport"]) > 0)
        return true;

    errStr << "Het bestand bevat foute informatie voor de hub" << endl;
    return false;
}

bool simulationImporter::checkName(string name) {
    return (name == "VACCIN" || name == "CENTRA"
            || name == "naam" || name == "adres" || name == "inwoners" || name == "capaciteit");
}

bool simulationImporter::checkElementName(string elementName) {
    return (elementName == "HUB" || elementName == "VACCINATIECENTRUM" );
}

int simulationImporter::importFile(string inFile, simulation &sim, ostream& errStr) {
    sim.clear();
    TiXmlDocument doc;
    map<string, Centrum *> centraMap;
    vector<Vaccine*> vaccins;
    Hub *h;

    //Consistentie check
    int hubCount = 0;

    if (!doc.LoadFile(inFile.c_str())) {
        errStr << "Error reading " + inFile + ": " << doc.ErrorDesc() << endl;
        return 1;
    }

    if (!doc.FirstChildElement()->FirstChildElement()) {
        errStr << "empty root in file: " + inFile << endl;
        return 1;
    }

    TiXmlElement *root = doc.FirstChildElement();

    //intereert over hubs en centra
    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        map<string, string> elements;
        string name;
        string elementName = elem->Value();

        if (!elem->FirstChild()){
            errStr << "empty element in " << elementName << endl;
            continue;
        }

        if (!checkElementName(elementName)) {
            errStr << "Kan element niet herkennen" << endl;
            continue;
        }

        //ittereert over elementen in hubs en centra
        for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
            name = ele->Value();
            if (!checkName(name)) {
                errStr << "Kan element " + name + " niet herkennen in " << elementName << endl;
                continue;
            }
            else if (name == "VACCIN"){ // Een vaccins in de hub
                Vaccine *vaccin;
                vaccin = new Vaccine;
                bool insert;
                for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
                    insert = vaccin->insert(el, errStr);
                    if (!insert)
                        break;
                }
                if (!insert) {
                    errStr << "Het bestand bevat foute informatie voor een VACCIN" << endl;
                    delete vaccin;
                    continue;
                }
                vaccins.push_back(vaccin);
            }
            else if (name != "CENTRA") {
                if (!ele->FirstChild()){
                    errStr << "empty element in " << name << endl;
                    continue;
                }
                elements[ele->Value()] = ele->FirstChild()->ToText()->Value();
            }
            else { // zet centra in een vector (enkel voor hubs)
                for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
                    if (!el->FirstChild()){
                        errStr << "empty centrum name in hub" << endl;
                        continue;
                    }
                    string tag = el->Value();
                    if (tag != "centrum") {
                        errStr << "Kan element " + tag + " niet herkennen" << endl;
                        continue;
                    }
                    string centerName = el->FirstChild()->ToText()->Value();
                    if (centraMap.find(centerName) != centraMap.end()) {
                        errStr << "Dubbele definitie van centrum in hub" << endl;
                        continue;
                    }
                    centraMap.insert(pair<string, Centrum *>(centerName, NULL));
                }
            }
        }

        if (elementName == "HUB") {
            hubCount++;
            h = new Hub(vaccins, centraMap);
            sim.setHub(h);
        } else if (elementName == "VACCINATIECENTRUM" && isCoorectCentrum(elements, errStr)) {
            Centrum *c = new Centrum(elements["naam"], elements["adres"], algemeen::stoi(elements["inwoners"]),
                                     algemeen::stoi(elements["capaciteit"]));
            sim.addCentrum(c);
        }
    }

    map<string, Centrum *>::iterator it;

    for (it = centraMap.begin(); it != centraMap.end(); it++) {
        int count = 0;
        string n = it->first;
        for (unsigned int i = 0; i < sim.getCentra().size(); i++) {
            if (n == sim.getCentra()[i]->getNaam())
                count++;

            if (centraMap.count(sim.getCentra()[i]->getNaam()) == 0) {
                errStr << "Niet elk vaccinatie centra is verbonden met een hub" << endl;
                return 2;
            }
            else
                centraMap[sim.getCentra()[i]->getNaam()] = sim.getCentra()[i];
        }

        if (count == 0) {
            errStr << "Niet elk centrum van de hub is een geldig vaccinatiecentrum" << endl;
            return 2;
        }
    }

    if (hubCount == 1)
        h->setCentra(centraMap);

    if (hubCount != 1) {
        errStr << "Er is niet exact 1 hub" << endl;
        return 2;
    }
    else if (sim.getCentra().size() == 0) {
        errStr <<"Er zijn minder dan 1 centra" << endl;
        return 2;
    }

    doc.Clear();
    return 0;
}
 */