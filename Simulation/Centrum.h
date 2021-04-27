/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which represents a vaccination center
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

#include <string>
#include <vector>
#include <map>
#include "Vaccine.h"

using namespace std;

/**
 * Class which represents a vaccination centre in the simulation
 */
class Centrum {
    Centrum* _initCheck;

    string naam;
    string adres;
    int inwoners;
    int capaciteit;
    int gevaccineerd;
    int eerste;
    map<Vaccine*, int> voorraad;
    map<pair<int, Vaccine*>, int> gevac;
public:
    //constructor
    Centrum();
    /**
     * Constructor
     * \n REQUIRE(i>=0, "inhabitant amount can't be negative");
       \n REQUIRE(c>=0, "capacity can't be negative");
     * \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
     * @param n:    Name
     * @param a:    Adres
     * @param i:    Inhabitants amount
     * @param c:    Capacity
     */
    Centrum(const string& n, const string& a, int i, int c);

    /**
     * Checks if propperly initialized
     * @return bool
     */
    bool properlyInitialised() const {return _initCheck == this; };

    /**
     * \n set voorraad of certain vaccine
     * @param vac:      The vaccine
     * @param aantal:   Stock of the vaccine
     */
    void setVoorraad(Vaccine* vac, int aantal);
    /**
     * Get voorrad map van alle vaccins
     * @return map<Vaccine*, int> {type: voorraad, ...}
     */
    map<Vaccine*, int> getVoorraad();
    /**
     * Voeg toe aan de voorraad van een bepaald vaccin
     * @param vac:      Vacccin waaraan toe te voegen
     * @param aantal:   Toe te voegen aantal
     */
    void verhoogVoorraad(Vaccine* vac, int aantal);
    /**
     * Verlaag de voorraad van een bepaald vaccin
     * @param vac:      Te verlagen vaccin
     * @param aantal:   Te verlagen aantal
     */
    void verlaagVoorraad(Vaccine* vac, int aantal);

    /**
     \n Set amount of vaccinated people in center
     * @param g :   Amount of vaccinated people
     */
    void setGevaccineerd(int g);

    /**
     \n getter for name
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getNaam");
     * @return string name
     */
    const string &getNaam() const;
    /**
     \n getter for address
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getAdres");
     * @return string address
     */
    const string &getAdres() const;
    /**
     \n getter for inhabitants
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins");
     \n ENSURE(amount>=0, "getInwoners postconditions failed");
     * @return int inhabitants
     */
    int getInwoners() const;
    /**
     \n getter for capacity
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getCapaciteit");
     \n ENSURE(amount>=0, "getCapaciteit postconditions failed");
     * @return int
     */
    int getCapaciteit() const;
    /**
     \n Get total amount of vaccines in center
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVaccins");
     \n ENSURE((amount>=0) && (amount<=getCapaciteit()*2), "getVaccins postconditions failed");
     * @return int
     */
    int getVaccins();
    /**
     * \n getter for vaccinated
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd");
       \n ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed");
     * @return int
     */
    int getGevaccineerd() const;

    /**
     \n Calculate amount af deliveries for vaccine
     * @param vaccin
     * @param dag
     * @return
     */
    int berekenLadingen(Vaccine* vaccin, int dag);

    /**
     * Print een transport van een bepaald vaccin
     * @param vaccins
     * @param vaccin
     * @param onStream
     */
    void printTransport(int vaccins,Vaccine* vaccin, ostream& onStream);

    /**
     * Print een eerste vaccinatie
     * @param vaccins
     * @param vaccin
     * @param onStream
     */
    void printEersteVaccinatie(int vaccins,Vaccine* vaccin, ostream& onStream);

    /**
     * Print een tweede vaccinatie
     * @param vaccins
     * @param vaccin
     * @param onStream
     */
    void printTweedeVaccinatie(int vaccins,Vaccine* vaccin, ostream& onStream);
    // Zet de vaccins
    void zetVaccinatie(int dag, Vaccine* vac, int aantal);
    // vraag lijst eerste vaccinaties { (dag, vaccin): aantal, ... }
    map<pair<int, Vaccine*>, int> getGevac();
    // Verhoog aantal gevaccineerden
    void verhoogGevaccineerd(int aantal);
    // Vraag aantal mensen met eerste prik
    int getEerste();
    // Verhoog aantal mensen met eerste prik
    void verhoogEerste(int aantal);
};


#endif //PROJECT_CENTRUM_H
