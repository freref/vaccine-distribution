//
// Created by frehml on 22/04/2021.
//

#include "Vaccine.h"

void Vaccine::insert(TiXmlElement* el) {
    if(strcmp(el->Value(), "type") == 0){
        type = (el->FirstChild()->ToText()->Value());
    }
    else if(strcmp(el->Value(), "levering") == 0){
        levering = (stoi(el->FirstChild()->ToText()->Value()));
        voorraad = levering;
    }
    else if(strcmp(el->Value(), "interval") == 0){
        interval = (stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "transport") == 0){
        transport = (stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "hernieuwing") == 0){
        hernieuwing = (stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "temperatuur") == 0){
        temperatuur = (stoi(el->FirstChild()->ToText()->Value()));
    }
}

void Vaccine::verlaagVaccins(int vaccins){
    setVoorraad(getVoorraad()-vaccins);
}

void Vaccine::setVoorraad(int v){
    this->voorraad = v;
}

string Vaccine::getType(){
    return type;
}

int Vaccine::getVoorraad(){
    return voorraad;
}

int Vaccine::getInterval(){
    return interval;
}

int Vaccine::getLevering(){
    return levering;
}

int Vaccine::getTransport(){
    return transport;
}

int Vaccine::getHernieuwing(){
    return hernieuwing;
}