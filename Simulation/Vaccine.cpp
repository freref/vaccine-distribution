/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which handles the automation of the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    12/3/2021
 * @version 1.0
 */
 
#include "Vaccine.h"
#include "algemeen.h"
#include "DesignByContract.h"

Vaccine::Vaccine() {
    _initCheck = this;
    type = "";
    levering = 0;
    interval = 0;
    transport = 0;
    voorraad = 0;
    hernieuwing = 0;
    temperatuur = 0;
    ENSURE(this->properlyInitialised(), "Constructor must end properly initialised");
}

bool Vaccine::properlyInitialised() const {
    return _initCheck == this;
}

bool Vaccine::insert(TiXmlElement* el, ostream& errStr) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when inserting data");
    if (!el->FirstChild()) {
        errStr << "empty element in vaccine" << endl;
        return false;
    }
    string str = el->FirstChild()->ToText()->Value();
    if(strcmp(el->Value(), "type") == 0){
        // string val = (el->FirstChild()->ToText()->Value());
        if (str == "")
            return false;
        type = str;
    }
    else if(strcmp(el->Value(), "levering") == 0){
        int val = algemeen::stoi(str); // (algemeen::stoi(el->FirstChild()->ToText()->Value()));
        if (val < 0)
            return false;
        levering = val;
    }
    else if(strcmp(el->Value(), "interval") == 0){
        int val = algemeen::stoi(str);
        if (val < 0)
            return false;
        interval = val;
    }
    else if(strcmp(el->Value(), "transport") == 0){
        int val = algemeen::stoi(str);
        if (val < 0)
            return false;
        transport = val;
    }
    else if(strcmp(el->Value(), "hernieuwing") == 0){
        int val = algemeen::stoi(str);
        if (val < 0)
            return false;
        hernieuwing = val;
    }
    else if(strcmp(el->Value(), "temperatuur") == 0){
        temperatuur = algemeen::stoi(str);
    } else {
        errStr << "Kan element " << el->Value() << " niet herkennen in VACCINE" << endl;
    }
    return true;
}

void Vaccine::verlaagVaccins(int vaccins){
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when lowering vaccines");
    int oVoorraad = voorraad;
    setVoorraad(getVoorraad()-vaccins);
    ENSURE(oVoorraad == getVoorraad() + vaccins, "Vaccine supply didn't lower correctly");
}

//
// Setters
//

void Vaccine::setType(string &t) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting type");
    type = t;
    ENSURE(getType() == t, "setType postcondition failed");
}

void Vaccine::setLevering(int l) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting levering");
    REQUIRE(l >= 0, "Vaccine can't have negative levering");
    levering = l;
    ENSURE(getLevering() == l, "setLevering postcondition failed");
}

void Vaccine::setInterval(int i) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting interval");
    REQUIRE(i >= 0, "Vaccine can't have negative interval");
    interval = i;
    ENSURE(getInterval() == i, "setInterval postcondition failed");
}

void Vaccine::setTransport(int t) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting transport");
    REQUIRE(t > 0, "Vaccine transport must be bigger than 0");
    transport= t;
    ENSURE(getTransport() == t, "setTransport postcondition failed");
}

void Vaccine::setVoorraad(int v){
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting stock");
    REQUIRE(v >= 0, "Vaccine can't have negative stock");
    voorraad = v;
    ENSURE(getVoorraad() == v, "setVoorraad postcondition failed");
}

void Vaccine::setHernieuwing(int h) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting hernieuwing");
    REQUIRE(h >= 0, "Vaccine can't have negative renewal");
    hernieuwing = h;
    ENSURE(getHernieuwing() == h, "setHernieuwing postcondition failed");
}

void Vaccine::setTemperatuur(int t) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting temperature");
    temperatuur = t;
    ENSURE(getTemperatuur() == t, "setTemperature postcondition failed");
}

//
// Getters
//

string Vaccine::getType() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting type");
    return type;
}

int Vaccine::getLevering() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting levering");
    return levering;
}

int Vaccine::getInterval() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting interval");
    return interval;
}

int Vaccine::getTransport() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting transport");
    return transport;
}

int Vaccine::getVoorraad() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting stock");
    return voorraad;
}

int Vaccine::getHernieuwing() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting renewal");
    return hernieuwing;
}

int Vaccine::getTemperatuur() const {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when getting temperature");
    return temperatuur;
}