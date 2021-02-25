#include <iostream>
#include "tinyxml.h"
#include <vector>
#include "Centrum.h"
#include "Hub.h"
#include <string>
#include <map>

using namespace std;

void parse(TiXmlDocument* doc, vector<Centrum>* centra, vector<Hub>* hubs){
    TiXmlElement* root = doc->FirstChildElement();
    vector<string> c; // vector voor centra in hubs
    string elementName;

    //intereert over hubs en centra
    for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()){
        map<string, string> elements;
        string name;

        //ittereert over elementen in hubs en centra
        for(TiXmlElement* ele = elem->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement()){
            name = ele->Value();
            if(name != "CENTRA")
                elements[ele->Value()] = ele->FirstChild()->ToText()->Value();
            else{ // zet centra in een vector (enkel voor hubs)
                for(TiXmlElement* el = ele->FirstChildElement(); el != nullptr; el = el->NextSiblingElement()){
                    c.push_back(el->FirstChild()->ToText()->Value());
                }
            }
        }

        elementName = elem->Value();

        if(elementName == "HUB")
            hubs->push_back(Hub(stoi(elements["levering"]), stoi(elements["interval"]), stoi(elements["transport"]), c));
        else if (elementName == "VACCINATIECENTRUM")
            centra->push_back(Centrum(elements["naam"], elements["adres"], stoi(elements["inwoners"]), stoi(elements["capaciteit"])));

    }
}

int main() {
    TiXmlDocument doc;
    vector<Centrum> centra;
    vector<Hub> hubs;

    if(!doc.LoadFile("data1.xml")) {
        cerr << doc.ErrorDesc() << endl;
        return 1;
    }

    parse(&doc, &centra, &hubs);

    if (hubs.empty())
        cerr << "no hubs found";

    if (centra.empty())
        cerr << "no centra found";

    return 0;
}