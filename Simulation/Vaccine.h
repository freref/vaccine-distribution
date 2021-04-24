//
// Created by frehml on 22/04/2021.
//

#ifndef PROJECT_VACCINE_H
#define PROJECT_VACCINE_H

#include <string>
#include <iostream>
#include "../XmlParser/tinyxml.h"

using namespace std;

class Vaccine {
    string type;
    int levering;
    int interval;
    int transport;
    int voorraad;
    int hernieuwing;
    int temperatuur;

public:
    void insert(TiXmlElement* el);
    void verlaagVaccins(int vaccins);

    void setType(string t);
    void setLevering(int l);
    void setInterval(int i);
    void setTransport(int t);
    void setVoorraad(int v);
    void setHernieuwing(int h);
    void setTemperatuur(int t);

    string getType();
    int getVoorraad();
    int getInterval();
    int getLevering();
    int getTransport();
};


#endif //PROJECT_VACCINE_H
