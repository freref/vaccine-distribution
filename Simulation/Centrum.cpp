/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Definitions for the Centrum class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#include "Centrum.h"
#include "DesignByContract.h"

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


void Centrum::setVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = aantal;
}

map<Vaccine*, int> Centrum::getVoorraad(){
    return voorraad;
}

void Centrum::verhoogVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] = getVoorraad()[vac] + aantal;
}

void Centrum::verlaagVoorraad(Vaccine* vac, int aantal){
    voorraad[vac] -= aantal;
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
    int amount = 0;
    map<Vaccine*, int> v = getVoorraad();
    for (map<Vaccine*, int>::iterator it = v.begin(); it != v.end(); it++) {
        amount += it->second;
    }
    return amount;
}

int Centrum::getGevaccineerd() const {
    REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd");
    int amount = gevaccineerd;
    ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed");
    return amount;
}

int Centrum::berekenEerstePrikLadingen(Vaccine* vaccin, int dag, int devide) {
    REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling berekenLadingen");
    int transport = vaccin->getTransport();
    int vaccins = getVaccins();
    int dev = (vaccin->getInterval()+1-(dag%(vaccin->getInterval()+1)));
    int v = vaccin->getVoorraad();
    int accounted = v/devide/dev;
    int ladingen = 0;

    //for loop met alle condities van appendix B
    // Lading verder kijken dan huidige (om na te kijken) om niet op volgende over parameters te gaan
    if(vaccin->getTemperatuur() >= 0){
        while ((ladingen+1)*transport <= v && (ladingen+1)*transport+vaccins <= 2*capaciteit) {
            // Afbreken wanneer voldaan aan capaciteit
            if (ladingen*transport + vaccins >= capaciteit || ladingen*transport + vaccins >= accounted)
                break;
            ladingen += 1;
        }
    }
    else{
        while ((ladingen+1)*transport <= v && (ladingen+1)*transport+vaccins <= capaciteit) {
            if (ladingen*transport + vaccins >= accounted)
                break;
            ladingen += 1;
        }
    }

    ENSURE(ladingen>=0, "berekenLadingen postconditions failed");
    return ladingen;
}

int Centrum::berekenTweedePrikLadingen(Centrum* c, Vaccine* vaccin, int aantal){
    int v = min(aantal, min(vaccin->getVoorraad(), c->getCapaciteit()*2 - c->getVaccins()));
    int ladingen = v/vaccin->getTransport();

    if (v > 0 && ladingen == 0)
        ladingen = 1;

    return ladingen;
}

void Centrum::printTransport(int vaccins, Vaccine* vaccin, ostream& onStream) const {
    REQUIRE(vaccins >= 0, "vaccins amount can't be negative");
    int ladingen = vaccins/vaccin->getTransport();
    if (ladingen == 0){
        ladingen = 1;
    }
    onStream << "Er werden " << ladingen << " ladingen " << vaccin->getType() << " (" << vaccins << " vaccins)"
             << " getransporteerd naar "<< getNaam() <<"." << endl;
}

void Centrum::printEersteVaccinatie(int vaccinaties, Vaccine* vaccin, ostream& onStream) const {
    onStream << "Er werden " << vaccinaties << " inwoners voor de eerste keer gevaccineerd in " << getNaam() << " met het "<< vaccin->getType()<<" vaccin." << endl;
}

void Centrum::printTweedeVaccinatie(int vaccinaties, Vaccine* vaccin, ostream& onStream) const {
    onStream << "Er werden " << vaccinaties << " inwoners voor de tweede keer gevaccineerd in " << getNaam() << " met het "<< vaccin->getType()<<" vaccin." << endl;
}

void Centrum::verhoogGevaccineerd(int aantal){
    gevaccineerd += aantal;
}

void Centrum::zetVaccinatie(int dag, Vaccine* vac, int aantal){
    gevac[pair<int, Vaccine*>(dag, vac)] += aantal;
}

map<pair<int, Vaccine*>, int> Centrum::getGevac(){
    return gevac;
}

int Centrum::getEerste() const{
    return eerste;
}

void Centrum::verhoogEerste(int aantal){
    eerste += aantal;
}