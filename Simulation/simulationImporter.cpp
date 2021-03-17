
/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the simulationImporter class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    4/3/2021
 * @version 1.0
 */

#include <iostream>
#include <sstream>

#include "Hub.h"
#include "Centrum.h"
#include "simulation.h"

#include "simulationImporter.h"
#include "../XmlParser/tinyxml.h"

// https://stackoverflow.com/questions/4442658/c-parse-int-from-string
int stoi(string &s) {
    if (s.empty())
        throw std::invalid_argument("conversion from invalid string to int");
    for (long unsigned int j=0; j<s.size(); j++) {
        if ((s[j] < '0' || s[j] > '9') && s[j] != '-')
            throw std::invalid_argument("conversion from invalid string to int");
    }
    int i;
    istringstream(s) >> i;
    return i;
}

bool simulationImporter::isCoorectCentrum(map<string, string> elements, ostream& errStr) {
    if (elements["naam"] != "" && elements["adres"] != "" && stoi(elements["inwoners"]) > 0 &&
        stoi(elements["capaciteit"]) > 0)
        return true;

    errStr << "Het bestand bevat foute informatie voor vaccinatiecentrum: " << elements["naam"] << endl;
    return false;
}


bool isCorrectHub(map<string, string> elements, ostream& errStr) {
    if (stoi(elements["levering"]) > 0 && stoi(elements["interval"]) > 0 && stoi(elements["transport"]) > 0)
        return true;

    errStr << "Het bestand bevat foute informatie voor de hub" << endl;
    return false;
}

bool simulationImporter::checkName(string name) {
    return (name == "levering" || name == "interval" || name == "transport" || name == "CENTRA"
            || name == "naam" || name == "adres" || name == "inwoners" || name == "capaciteit");
}

bool simulationImporter::checkElementName(string elementName) {
    return (elementName == "HUB" || elementName == "VACCINATIECENTRUM" );
}

int simulationImporter::importFile(string inFile, simulation &sim, ostream& errStr) {
    sim.clear();
    TiXmlDocument doc;
    map<string, Centrum *> centraMap;
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

        //ittereert over elementen in hubs en centra
        for (TiXmlElement *ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()) {
            name = ele->Value();
            if (!checkName(name)) {
                errStr << "Kan element " + name + " niet herkennen" << endl;
                continue;
            }
            if (name != "CENTRA") {
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

        if (!checkElementName(elementName)) {
            errStr << "Kan element niet herkennen" << endl;
            continue;
        }

        if (elementName == "HUB" && isCorrectHub(elements, errStr)) {
            hubCount++;
            h = new Hub(stoi(elements["levering"]), stoi(elements["interval"]),
                        stoi(elements["transport"]), centraMap);
            sim.setHub(h);
        } else if (elementName == "VACCINATIECENTRUM" && isCoorectCentrum(elements, errStr)) {
            Centrum *c = new Centrum(elements["naam"], elements["adres"], stoi(elements["inwoners"]),
                                     stoi(elements["capaciteit"]));
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