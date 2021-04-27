//
// Created by frehml on 22/04/2021.
//

#include "Vaccine.h"
#include "algemeen.h"
#include "DesignByContract.h"

Vaccine::Vaccine() {
    _initCheck = this;
    voorraad = 0;
    ENSURE(this->properlyInitialised(), "Constructor must end properly initialised");
}

bool Vaccine::properlyInitialised() const {
    return _initCheck == this;
}

void Vaccine::insert(TiXmlElement* el) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when inserting data");
    if(strcmp(el->Value(), "type") == 0){
        type = (el->FirstChild()->ToText()->Value());
    }
    else if(strcmp(el->Value(), "levering") == 0){
        levering = (algemeen::stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "interval") == 0){
        interval = (algemeen::stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "transport") == 0){
        transport = (algemeen::stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "hernieuwing") == 0){
        hernieuwing = (algemeen::stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "temperatuur") == 0){
        temperatuur = (algemeen::stoi(el->FirstChild()->ToText()->Value()));
    }
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
    levering = l;
    ENSURE(getLevering() == l, "setLevering postcondition failed");
}

void Vaccine::setInterval(int i) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting interval");
    interval = i;
    ENSURE(getInterval() == i, "setInterval postcondition failed");
}

void Vaccine::setTransport(int t) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting transport");
    transport= t;
    ENSURE(getTransport() == t, "setTransport postcondition failed");
}

void Vaccine::setVoorraad(int v){
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting stock");
    voorraad = v;
    ENSURE(getVoorraad() == v, "setVoorraad postcondition failed");
}

void Vaccine::setHernieuwing(int h) {
    REQUIRE(this->properlyInitialised(), "Vaccine wasn't initialised when setting hernieuwing");
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