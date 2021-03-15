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

int stoi(string& s) {
    int i;
    istringstream(s) >> i;
    return i;
}

int simulationImporter::importFile(const string &inFile, simulation &sim) {
    TiXmlDocument doc;

    if(!doc.LoadFile("data1.xml")) {
        cerr << "Error reading file: " << doc.ErrorDesc() << endl;
        return 1;
    }

    TiXmlElement* root = doc.FirstChildElement();
    string elementName;

    map<string, Centrum*> centraMap;
    Hub* h;

    //intereert over hubs en centra
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        map<string, string> elements;
        string name;

        //ittereert over elementen in hubs en centra
        for(TiXmlElement* ele = elem->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement()){
            name = ele->Value();
            if(name != "CENTRA")
                elements[ele->Value()] = ele->FirstChild()->ToText()->Value();
            else{ // zet centra in een vector (enkel voor hubs)
                for(TiXmlElement* el = ele->FirstChildElement(); el != NULL; el = el->NextSiblingElement()){
                    centraMap.insert(pair<string, Centrum*>(el->FirstChild()->ToText()->Value(), NULL));
                }
            }
        }

        elementName = elem->Value();

        if(elementName == "HUB") {
            h = new Hub(stoi(elements["levering"]), stoi(elements["interval"]), stoi(elements["transport"]), centraMap);
            sim.setHub(h);
        }
        else if (elementName == "VACCINATIECENTRUM") {
            Centrum* c = new Centrum(elements["naam"], elements["adres"], stoi(elements["inwoners"]),stoi(elements["capaciteit"]));
            sim.addCentrum(c);
            centraMap[elements["naam"]] = c;
        }

    }
    h->setCentra(centraMap);
    return 0;
}
