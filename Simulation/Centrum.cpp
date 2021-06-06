/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the Centrum class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include <cmath>
#include "Centrum.h"
#include "DesignByContract.h"
#include "algemeen.h"

Centrum::Centrum() {
    naam = "";
    adres = "";
    inwoners = 0;
    capaciteit = 0;
    gevaccineerd = 0;
    eerste = 0;
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

Centrum::Centrum(const string &n, const string &a, int i, int c) {
    REQUIRE(i>=0, "inhabitant amount can't be negative");
    REQUIRE(c>=0, "capacity can't be negative");
    naam = n;
    adres = a;
    inwoners = i;
    capaciteit = c;
    gevaccineerd = 0;
    eerste = 0;
    _initCheck = this;
    ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
}

bool Centrum::empty(){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when checking empty");
    return( naam == "" &&
        adres == "" &&
        inwoners == 0 &&
        capaciteit == 0 &&
        gevaccineerd == 0 &&
        eerste == 0);
}

bool Centrum::insert(TiXmlElement *el, ostream& errStr){
    if (!el->FirstChild()) {
        errStr << "empty element in centrum" << endl;
        return false;
    }
    string str = el->FirstChild()->ToText()->Value();
    if(strcmp(el->Value(), "naam") == 0){
        if (str == ""){
            errStr << "Naam is empty" << endl;
            return false;
        }
        naam = str;
    }
    else if(strcmp(el->Value(), "adres") == 0){
        if (str == ""){
            errStr << "Adres is empty" << endl;
            return false;
        }
        adres = str;
    }
    else if(strcmp(el->Value(), "inwoners") == 0){
        int val = algemeen::stoi(str);
        if (val < 0){
            errStr << "Inwoners is less than 0" << endl;
            return false;
        }
        inwoners = val;
    }
    else if(strcmp(el->Value(), "capaciteit") == 0){
        int val = algemeen::stoi(str);
        if (val < 0){
            errStr << "Capaciteit is less than 0" << endl;
            return false;
        }
        capaciteit = val;
    } else {
        errStr << "Couldn't recognise element " << el->Value() << " in VACCIN" << endl;
        return false;
    }
    return true;
}


void Centrum::setVoorraad(Vaccine* vac, int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVoorraad");
    voorraad[vac] = aantal;
    ENSURE(getVoorraad()[vac] == aantal, "setVoorraad postcondition failed");
}

map<Vaccine*, int> Centrum::getVoorraad(){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVoorraad");
    return voorraad;
}

void Centrum::verhoogVoorraad(Vaccine* vac, int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogVoorraad");
    REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling verhoogVoorraad");
    int oAmount = getVoorraad()[vac];
    voorraad[vac] += aantal;
    ENSURE(getVoorraad()[vac]-aantal == oAmount, "verhoogVoorraad postcondition failed");
}

void Centrum::verlaagVoorraad(Vaccine* vac, int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verlaagVoorraad");
    REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling verlaagVoorraad");
    int oAmount = getVoorraad()[vac];
    voorraad[vac] -= aantal;
    ENSURE(getVoorraad()[vac]+aantal == oAmount, "verlaagVoorraad postcondition failed");
}


void Centrum::setGevaccineerd(int g) {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setGevaccineerd");
    REQUIRE(g>=0, "gevaccineerd can't be negative");
    REQUIRE(g<=getInwoners(), "gevaccineerd amount can't be bigger than inhabitants amount");
    gevaccineerd = g;
    ENSURE(getGevaccineerd() == g, "setGevaccineerd postcondition failed");
}

const string & Centrum::getNaam() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getNaam");
    return naam;
}

const string & Centrum::getAdres() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getAdres");
    return adres;
}

int Centrum::getInwoners() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
    int amount = inwoners;
    ENSURE(amount>=0, "getInwoners postconditions failed");
    return amount;
}

int Centrum::getCapaciteit() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getCapaciteit");
    int amount = capaciteit;
    ENSURE(amount>=0, "getCapaciteit postconditions failed");
    return amount;
}

int Centrum::getVaccins() {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVaccins");
    int amount = 0;
    map<Vaccine*, int> v = getVoorraad();
    for (map<Vaccine*, int>::iterator it = v.begin(); it != v.end(); it++) {
        amount += it->second;
    }
    ENSURE((amount>=0) && (amount<=getCapaciteit()*2), "getVaccins postconditions failed");
    return amount;
}

int Centrum::getGevaccineerd() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd");
    int amount = gevaccineerd;
    ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed");
    return amount;
}

int Centrum::berekenEerstePrikLadingen(Hub* hub, Vaccine* vaccin, int dag, int devide) {
    REQUIRE(this->properlyInitialised(),
            "simulation wasn't initialised when calling berekenEerstePrikLadingen");
    REQUIRE(vaccin->properlyInitialised(),
            "vaccine wasn't initialised when calling berekenEerstePrikLadingen");
    REQUIRE(dag >= 0, "transport day can't be negative");
    REQUIRE(devide >= 0, "division can't be negative");
    int transport = vaccin->getTransport(); // Vaccins in transport
    int vaccins = getVaccins(); // Huidig aantal aanwezig vaccins
    // overig dagen tot nieuwe voorraad vaccins in hub
    int dev = (vaccin->getInterval()+1-(dag%(vaccin->getInterval()+1)));
    int v = hub->getVoorraad(vaccin); // Vaccins van type in hub
    int accounted = /*v/*/ devide/dev; // Hoeveel mogelijk uit te delen om zo veel mogelijk te stretchen
    int ladingen = 0; // Aantal ladingen


    if(vaccin->getTemperatuur() >= 0){ // Vaccin bewaard boven 0 graden, geen speciale conditie
        while ((ladingen+1)*transport <= v && (ladingen+1)*transport+vaccins <= 2*capaciteit) {
            // Afbreken wanneer voldaan aan capaciteit
            if (ladingen*transport + vaccins >= capaciteit || ladingen*transport /*+ vaccins*/ >= accounted)
                break;
            ladingen += 1;
        }
    }
    else{
        while ((ladingen+1)*transport <= v && (ladingen+1)*transport+vaccins <= capaciteit) {
            if (ladingen*transport /*+ vaccins*/ >= accounted)
                break;
            ladingen += 1;
        }
    }

    ENSURE(ladingen>=0, "berekenEerstePrikLadingen postconditions failed");
    return ladingen;
}

int Centrum::berekenTweedePrikLadingen(Hub* hub, Vaccine* vaccin, int aantal){
    REQUIRE(this->properlyInitialised(),
            "simulation wasn't initialised when calling berekenTweedePrikLadingen");
    REQUIRE(vaccin->properlyInitialised(),
            "vaccine wasn't initialised when calling berekenTweedePrikLadingen");
    REQUIRE(aantal >= 0, "transport can't have negative amount of vaccines");

    if (aantal <= voorraad[vaccin])
        return 0;

    int v = min(aantal, min(hub->getVoorraad(vaccin), getCapaciteit()*2 - getVaccins()));
    int ladingen = ceil(float (v)/vaccin->getTransport());

    if (v > 0 && ladingen == 0)
        ladingen = 1;

    while (ladingen*vaccin->getTransport() + getVaccins() > getCapaciteit()*2 && ladingen > 0)
        ladingen -= 1;

    if (vaccin->getTemperatuur() <= 0) {
        while (ladingen*vaccin->getTransport() + getVaccins() > getCapaciteit() && ladingen-1 > 0)
            ladingen -= 1;
    }
    ENSURE(ladingen >= 0, "berekenTweedePrikLadingen postconditions failed");
    return ladingen;
}

void Centrum::printTransport(int vaccins, Vaccine* vaccin, ostream& onStream) const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling printTransport");
    REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling printTransport");
    REQUIRE(vaccins >= 0, "can't transport negative amount of vaccines");

    int ladingen = vaccins/vaccin->getTransport();
//    if (ladingen == 0){
//        ladingen = 1;
//    }
    onStream << "Er werden " << ladingen << " ladingen " << vaccin->getType() << " (" << vaccins << " vaccins)"
             << " getransporteerd naar "<< getNaam() <<"." << endl;
}

void Centrum::printEersteVaccinatie(int vaccinaties, Vaccine* vaccin, ostream& onStream) const {
    REQUIRE(this->properlyInitialised(),
            "centrum wasn't initialised when calling printEersteVaccinatie");
    REQUIRE(vaccin->properlyInitialised(),
            "vaccine wasn't initialised when calling printEersteVaccinatie");
    REQUIRE(vaccinaties >= 0, "can't vaccinate negative amount of people");

    onStream << "Er werden " << vaccinaties << " inwoners voor de eerste keer gevaccineerd in " << getNaam()
             << " met het "<< vaccin->getType()<<" vaccin." << endl;
}

void Centrum::printTweedeVaccinatie(int vaccinaties, Vaccine* vaccin, ostream& onStream) const {
    REQUIRE(this->properlyInitialised(),
            "centrum wasn't initialised when calling printTweedeVaccinatie");
    REQUIRE(vaccin->properlyInitialised(),
            "vaccine wasn't initialised when calling printTweedeVaccinatie");
    REQUIRE(vaccinaties >= 0, "can't vaccinate negative amount of people");

    onStream << "Er werden " << vaccinaties << " inwoners voor de tweede keer gevaccineerd in " << getNaam()
             << " met het "<< vaccin->getType()<<" vaccin." << endl;
}

void Centrum::verhoogGevaccineerd(int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogGevaccineerd");
    gevaccineerd += aantal;
}

void Centrum::zetVaccinatie(int dag, Vaccine* vac, int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling zetVaccinatie");
    REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling zetVaccinatie");
    REQUIRE(dag >= 0, "vaccination day can't be negative");
    gevac[pair<int, Vaccine*>(dag, vac)] += aantal;
}

map<pair<int, Vaccine*>, int> Centrum::getGevac(){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevac");
    return gevac;
}

void Centrum::removeVaccinatie(int dag, Vaccine *vac) {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling removeVaccinatie");
    REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling removeVaccinatie");
    REQUIRE(dag >= 0, "day can't be negative");
    gevac.erase(pair<int, Vaccine*>(dag, vac));
}

int Centrum::getEerste() const{
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getEerste");
    return eerste;
}

void Centrum::verhoogEerste(int aantal){
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogEerste");
    eerste += aantal;
}