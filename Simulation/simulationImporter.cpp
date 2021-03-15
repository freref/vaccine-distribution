/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Definitions for the simulationImporter class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 1.0
 */

#include <iostream>
#include <sstream>
#include <map>

#include "Hub.h"
#include "Centrum.h"
#include "simulation.h"

#include "simulationImporter.h"
#include "../XmlParser/tinyxml.h"

int stoi(string &s) {
    int i;
    istringstream(s) >> i;
    return i;
}

bool simulationImporter::isCoorectCentrum(map<string, string> elements) {
    if (elements["naam"] != "" && elements["adres"] != "" && stoi(elements["inwoners"]) > 0 &&
        stoi(elements["capaciteit"]) > 0)
        return true;

    cerr << "Het bestand bevat foute informatie voor vaccinatiecentrum: " << elements["naam"];
    return false;
}


bool isCorrectHub(map<string, string> elements) {
    if (stoi(elements["levering"]) > 0 && stoi(elements["interval"]) > 0 && stoi(elements["transport"]) > 0)
        return true;

    cerr << "Het bestand bevat foute informatie voor de hub";
    return false;
}

bool simulationImporter::checkName(string name) {
    return (name == "levering" || name == "interval" || name == "transport" || name == "CENTRA"  || name == "naam" || name == "adres" || name == "inwoners" || name == "capaciteit");
}

bool simulationImporter::checkElementName(string elementName) {
    return (elementName == "HUB" || elementName == "VACCINATIECENTRUM" );
}

int simulationImporter::importFile(string inFile, simulation &sim) {
    TiXmlDocument doc;
    map<string, Centrum *> centraMap;
    Hub *h;

    //Consistentie check
    int hubCount = 0;

    if (!doc.LoadFile(inFile.c_str())) {
        cerr << "Error reading file: " << doc.ErrorDesc() << endl;
        return 1;
    }

    TiXmlElement *root = doc.FirstChildElement();

    //intereert over hubs en centra
    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        map<string, string> elements;
        string name;

        //ittereert over elementen in hubs en centra
        for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
            name = ele->Value();
            if (!checkName(name)) {
                cerr << "Kan element niet herkennen";
                continue;
            }
            if (name != "CENTRA")
                elements[ele->Value()] = ele->FirstChild()->ToText()->Value();
            else { // zet centra in een vector (enkel voor hubs)
                for (TiXmlElement *el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
                    centraMap.insert(pair<string, Centrum *>(el->FirstChild()->ToText()->Value(), NULL));
                }
            }
        }

        string elementName = elem->Value();

        if (!checkElementName(elementName)) {
            cerr << "Kan element niet herkennen";
            continue;
        }

        if (elementName == "HUB" && isCorrectHub(elements)) {
            hubCount++;
            h = new Hub(stoi(elements["levering"]), stoi(elements["interval"]), stoi(elements["transport"]), centraMap);
            sim.setHub(h);
        } else if (elementName == "VACCINATIECENTRUM" && isCoorectCentrum(elements)) {
            Centrum *c = new Centrum(elements["naam"], elements["adres"], stoi(elements["inwoners"]),
                                     stoi(elements["capaciteit"]));
            sim.addCentrum(c);
        }
    }

    map<string, Centrum *>::iterator it;

    for (it = centraMap.begin(); it != centraMap.end(); it++) {
        int count = 0;
        string n = it->first;
        for (int i = 0; i < sim.getCentra().size(); i++) {
            if (n == sim.getCentra()[i]->getNaam())
                count++;

            if (centraMap.count(sim.getCentra()[i]->getNaam()) == 0)
                throw std::invalid_argument("Niet elk vaccinatie centra is verbonden met een hub");
            else
                centraMap[sim.getCentra()[i]->getNaam()] = sim.getCentra()[i];
        }

        if (count == 0) {
            throw std::invalid_argument("Niet elk centrum van de hub is een geldig vaccinatiecentrum");
        }
    }

    if (hubCount == 1)
        h->setCentra(centraMap);

    if (hubCount != 1)
        throw std::invalid_argument("Er is niet exact 1 hub");
    else if (sim.getCentra().size() == 0) {
        throw std::invalid_argument("Er zijn minder dan 1 centra");
    }

    doc.Clear();

    return 0;
}