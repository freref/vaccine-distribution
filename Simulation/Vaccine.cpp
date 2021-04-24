//
// Created by frehml on 22/04/2021.
//

#include "Vaccine.h"

void Vaccine::insert(TiXmlElement* el) {
    if(strcmp(el->Value(), "type") == 0){
        setType(el->FirstChild()->ToText()->Value());
    }
    else if(strcmp(el->Value(), "levering") == 0){
        setLevering(stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "interval") == 0){
        setInterval(stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "transport") == 0){
        setTransport(stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "voorraad") == 0){
        setVoorraad(stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "hernieuwing") == 0){
        setHernieuwing(stoi(el->FirstChild()->ToText()->Value()));
    }
    else if(strcmp(el->Value(), "temperatuur") == 0){
        setTemperatuur(stoi(el->FirstChild()->ToText()->Value()));
    }
}

void Vaccine::verlaagVaccins(int vaccins){
    setVoorraad(getVoorraad()-vaccins);
}

void Vaccine::setType(string t){
    this->type = t;
}
void Vaccine::setLevering(int l){
    this->levering = l;
    this->voorraad = l;
}
void Vaccine::setInterval(int i){
    this->interval = i;
}
void Vaccine::setTransport(int t){
    this->transport = t;
}
void Vaccine::setVoorraad(int v){
    this->voorraad = v;
}
void Vaccine::setHernieuwing(int h){
    this->hernieuwing = h;
}
void Vaccine::setTemperatuur(int t){
    this->temperatuur = t;
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